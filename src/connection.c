#include "connection.h"
#include <etch/response.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdbool.h>
#include <pthread.h>

typedef struct etch_handle_connection_args {
        int clientfd;
        struct EtchResponse (*handler)(char *buffer, size_t len);
} etch_handle_connection_args;

void *handle_connection(void *_args);

EtchServer etch_create_server(uint16_t port, int32_t max_pending_connections)
{
        int reuse = 1;
        EtchServer server = { 0 };

        // Create the socket
        if ((server.sockfd = socket(AF_INET6, SOCK_STREAM, 0)) < 0) {
                perror("socket() failed");
                exit(-1);
        }

        // Make socket reuse local address when server is restarted
        if (setsockopt(server.sockfd, SOL_SOCKET, SO_REUSEADDR, &reuse,
                       sizeof(reuse)) < 0) {
                perror("setsockopt(SO_REUSEADDR) failed");
                etch_destroy_server(server);
                exit(-1);
        }

        // Construct the address
        server.address.sin6_family = AF_INET6;
        server.address.sin6_addr = in6addr_any;
        server.address.sin6_port = htons(port);

        // Bind the server
        if (bind(server.sockfd, (struct sockaddr *)&server.address,
                 sizeof(server.address)) < 0) {
                perror("bind() failed");
                etch_destroy_server(server);
                exit(-1);
        }

        // Listen to the address
        if (listen(server.sockfd, max_pending_connections) < 0) {
                perror("listen() failed");
                etch_destroy_server(server);
                exit(-1);
        }

        printf("Listening on port %d\n", port);

        return server;
}

void etch_destroy_server(EtchServer server)
{
        fprintf(stderr, "Cleaning up\n");
        close(server.sockfd);
}

void etch_serve(uint16_t port,
                EtchResponse (*handler)(char *buffer, size_t len))
{
        EtchServer server = etch_create_server(port, 10);

        while (true) {
                struct sockaddr client_address;
                socklen_t client_address_length = sizeof(client_address);
                etch_handle_connection_args *args =
                        malloc(sizeof(etch_handle_connection_args));

                args->handler = handler;

                if ((args->clientfd = accept(server.sockfd, &client_address,
                                             &client_address_length)) < 0) {
                        perror("accept() failed");
                        continue; // Continue onto next request
                }

                pthread_t thread_id;
                pthread_create(&thread_id, NULL, handle_connection, args);
        }
}

void *handle_connection(void *_args)
{
        etch_handle_connection_args *args = _args;
        char *buffer = malloc(CONNECTION_BUFFER_SIZE * sizeof(char));

        ssize_t bytes_recieved =
                recv(args->clientfd, buffer, CONNECTION_BUFFER_SIZE, 0);

        if (bytes_recieved <= 0) {
                goto error;
        }
        EtchResponse res = args->handler(buffer, bytes_recieved);
        EtchResponseRaw res_raw = etch_response_serialize(res);
        send(args->clientfd, res_raw.bytes, res_raw.len, 0);
        etch_response_free(res);

error:
        close(args->clientfd);
        free(args);
        free(buffer);
        return NULL;
}
