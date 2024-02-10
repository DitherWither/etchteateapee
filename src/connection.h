#ifndef __CONNECTION_H__
#define __CONNECTION_H__

#include <stdint.h>
#include <arpa/inet.h>
#include <etch/response.h>

#define CONNECTION_BUFFER_SIZE 4096

typedef struct EtchServer {
        int32_t sockfd;
        struct sockaddr_in6 address;
} EtchServer;

void etch_destroy_server(EtchServer server);
void etch_serve(uint16_t port,
                EtchResponse (*handler)(char *buffer, size_t len));

#endif /* __CONNECTION_H__ */
