#ifndef __ETCH_ETCH_H__
#define __ETCH_ETCH_H__

#include <etch/request.h>
#include <etch/response.h>
#include <etch/server.h>
#include <etch/utils.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ETCH_PROGRAM(port)                              \
        EtchResponse handler(char *buffer, size_t len); \
        int32_t main()                                  \
        {                                               \
                etch_serve(port, handler);              \
                return 0;                               \
        }                                               \
        EtchResponse handler(char *buffer, size_t len)

#endif /* __ETCH_ETCH_H__ */
