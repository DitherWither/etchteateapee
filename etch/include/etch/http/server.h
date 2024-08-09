// SPDX-License-Identifier: LGPL-3.0-or-later
/**
 * @file server.h
 * @author Vardhan Patil (hi@vardhanpatil.com)
 * @brief HTTP Server and related macros
 * 
 * @copyright Copyright (c) 2024 Vardhan Patil
 * @lgpl
 */
#ifndef __ETCH_HTTP_SERVER_H__
#define __ETCH_HTTP_SERVER_H__

#include <stdint.h>
#include <etch/http/response.h>
#include <etch/http/request.h>

/**
 * @brief Start a multi threaded etch server with the given handler
 * 
 * On each request, the http request will be parsed, and the handler will then be 
 * called. The returned response struct will then be serialized into the http 
 * response 
 *
 * @param handler Function that will be called on every http request 
 */
void etch_serve(EtchResponse (*handler)(EtchRequest req));

#define ETCH_SERVER                                   \
        EtchResponse __etch_handler(EtchRequest req); \
        void __etch_init(int argc, char **argv);      \
        int32_t main(int argc, char **argv)           \
        {                                             \
                etch_config_init();                   \
                __etch_init(argc, argv);              \
                etch_serve(__etch_handler);           \
                return 0;                             \
        }

#define ETCH_INIT void __etch_init(int argc, char **argv)
#define ETCH_HANDLER EtchResponse __etch_handler(EtchRequest req)

#endif /* __ETCH_HTTP_SERVER_H__ */
