#include "connection.h"
#include <etch/response.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdbool.h>
#include <pthread.h>

struct etch_handle_connection_args {
        int clientfd;
        struct etch_response_raw (*handler)(char *buffer, size_t len);
};

void *handle_connection(void *_args);

struct etch_server etch_create_server(uint16_t port,
                                      int32_t max_pending_connections)
{
        int reuse = 1;
        struct etch_server server = { 0 };

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

void etch_destroy_server(struct etch_server server)
{
        fprintf(stderr, "Cleaning up\n");
        close(server.sockfd);
}

void etch_serve(uint16_t port, struct etch_response_raw (*handler)(char* buffer, size_t len))
{
        struct etch_server server = etch_create_server(port, 10);

        while (true) {
                struct sockaddr client_address;
                socklen_t client_address_length = sizeof(client_address);
                struct etch_handle_connection_args *args =
                        malloc(sizeof(struct etch_handle_connection_args));

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
        struct etch_handle_connection_args *args = _args;
        char* buffer = malloc(CONNECTION_BUFFER_SIZE * sizeof(char));

        ssize_t bytes_recieved = recv(args->clientfd, buffer, CONNECTION_BUFFER_SIZE, 0);

        if (bytes_recieved <= 0) {
                goto error;
        }
        struct etch_response_raw res = args->handler(buffer, bytes_recieved);
        send(args->clientfd, res.bytes, res.len, 0);
        free(res.bytes);

error:
        close(args->clientfd);
        free(args);
        free(buffer);
        return NULL;
}

