// SPDX-License-Identifier: LGPL-3.0-or-later
/**
 * @file request.h
 * @author Vardhan Patil (hi@vardhanpatil.com)
 * @brief HTTP requests and related functions/structs
 * 
 * @copyright Copyright (c) 2024 Vardhan Patil
 * @lgpl
 */
#ifndef __ETCH_HTTP_REQUEST_H__
#define __ETCH_HTTP_REQUEST_H__

#include <etch/http/header.h>

/**
 * @brief HTTP Request Method
 * 
 * As defined by RFC 2616 Section 5.1.1
 */
typedef enum EtchMethod {
        ETCH_METHOD_OPTIONS = 0,
        ETCH_METHOD_GET = 1,
        ETCH_METHOD_HEAD = 2,
        ETCH_METHOD_POST = 3,
        ETCH_METHOD_PUT = 4,
        ETCH_METHOD_DELETE = 5,
        ETCH_METHOD_TRACE = 6,
        ETCH_METHOD_CONNECT = 7,
        ETCH_METHOD_UNKNOWN = -1
} EtchMethod;

/**
 * @brief HTTP request struct
 */
typedef struct EtchRequest {
        EtchMethod method;
        char *path;
        EtchHeader *headers;
        size_t headers_count;
        char *body;
} EtchRequest;

/**
 * @brief Converts HTTP method enum to a string
 * 
 * @param method HTTP method as enum
 * @return const char* HTTP method as string
 */
const char *etch_method_to_string(EtchMethod method);

/**
 * @brief Converts HTTP method string to enum
 * 
 * @param str HTTP method as string
 * @return EtchMethod HTTP method as enum
 */
EtchMethod etch_method_from_string(const char *str);

/**
 * @brief Deserializes a HTTP request from string
 * 
 * @param str HTTP request as string 
 * @return EtchRequest Parsed HTTP request
 */
EtchRequest etch_request_from_string(const char *str);

/**
 * @brief Frees the memory of an HTTP request struct
 * 
 * @param request HTTP request to be freed
 */
void etch_free_request(EtchRequest request);

#endif /* __ETCH_HTTP_REQUEST_H__ */
