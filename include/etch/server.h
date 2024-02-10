#ifndef __ETCH_SERVER_H__
#define __ETCH_SERVER_H__

#include <stdint.h>
#include <etch/response.h>

void etch_serve(uint16_t port,
                EtchResponse (*handler)(char *buffer, size_t len));

#endif /* __ETCH_SERVER_H__ */
