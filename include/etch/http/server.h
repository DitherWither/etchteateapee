#ifndef __ETCH_SERVER_H__
#define __ETCH_SERVER_H__

#include <stdint.h>
#include <etch/http/response.h>
#include <etch/http/request.h>

void etch_serve(uint16_t port,
                EtchResponse (*handler)(EtchRequest req));

#define ETCH_SERVER_ON(port)                                   \
        EtchResponse __etch_handler(EtchRequest req); \
        void __etch_init(int argc, char **argv);               \
        int32_t main(int argc, char **argv)                    \
        {                                                      \
                __etch_init(argc, argv);                       \
                etch_serve(port, __etch_handler);              \
                return 0;                                      \
        }

#define ETCH_INIT void __etch_init(int argc, char **argv)
#define ETCH_HANDLER EtchResponse __etch_handler(EtchRequest req)

#define ETCH_SERVER_SIMPLE(port) \
        ETCH_SERVER_ON(port)     \
        ETCH_INIT                \
        {                        \
        }                        \
        ETCH_HANDLER

#endif /* __ETCH_SERVER_H__ */
