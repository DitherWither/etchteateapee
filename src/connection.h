#ifndef __CONNECTION_H__
#define __CONNECTION_H__

#include <stdint.h>
#include <arpa/inet.h>

#define CONNECTION_BUFFER_SIZE 4096

struct etch_server {
        int32_t sockfd;
        struct sockaddr_in6 address;
};

void etch_destroy_server(struct etch_server server);
void etch_serve(uint16_t port);

#endif /* __CONNECTION_H__ */
