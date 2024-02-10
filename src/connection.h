#ifndef __CONNECTION_H__
#define __CONNECTION_H__

#include <stdint.h>
#include <arpa/inet.h>
#include <etch/response.h>

#define CONNECTION_BUFFER_SIZE 4096

struct etch_server {
        int32_t sockfd;
        struct sockaddr_in6 address;
};

void etch_destroy_server(struct etch_server server);
void etch_serve(uint16_t port,
                struct etch_response_raw (*handler)(char *buffer, size_t len));
        
#endif /* __CONNECTION_H__ */
