#ifndef __ETCH_ETCH_H__
#define __ETCH_ETCH_H__

#include <etch/request.h>
#include <etch/response.h>
#include <etch/server.h>
#include <etch/utils.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

inline void _etch_empty_init(int _argc, char **_argv)
{
}

#define ETCH_SERVER_ON(port)                                   \
        EtchResponse __etch_handler(char *buffer, size_t len); \
        void __etch_init(int argc, char **argv);               \
        int32_t main(int argc, char **argv)                    \
        {                                                      \
                __etch_init(argc, argv);                       \
                etch_serve(port, __etch_handler);              \
                return 0;                                      \
        }

#define ETCH_INIT void __etch_init(int argc, char **argv)
#define ETCH_HANDLER EtchResponse __etch_handler(char *buffer, size_t len)

#define ETCH_SERVER_SIMPLE(port)   \
        ETCH_SERVER_ON(port) \
        ETCH_INIT            \
        {                    \
        }                    \
        ETCH_HANDLER

#endif /* __ETCH_ETCH_H__ */
