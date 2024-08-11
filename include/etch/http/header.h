// SPDX-License-Identifier: LGPL-3.0-or-later
/**
 * @file header.h
 * @author Vardhan Patil (hi@vardhanpatil.com)
 * @brief HTTP headers and related structs/functions
 * 
 * @copyright Copyright (c) 2024 Vardhan Patil
 * @lgpl
 */
#ifndef __ETCH_HTTP_HEADER_H__
#define __ETCH_HTTP_HEADER_H__

#include <stddef.h>

/**
 * @brief HTTP header struct 
 * 
 */
typedef struct EtchHeader {
        char *name;
        char *value;
} EtchHeader;

/**
 * @brief Converts an HTTP header struct to string
 * 
 * The returned string is heap allocated and should be freed by the caller 
 *
 * @param header HTTP header as struct 
 * @return char* HTTP header as string
 */
char *etch_header_to_string(EtchHeader header);

/**
 * @brief Takes an array of HTTP headers and body, and converts them into the headers block of the response
 *
 * The response body is used to calculate the `Content-Length` header
 *
 * @param headers Array of HTTP headers
 * @param headers_count Number of HTTP headers
 * @param body HTTP Response body
 * @return char* HTTP Headers block as string
 */
char *etch_headers_to_string(EtchHeader headers[], size_t headers_count,
                             const char *body);

/**
 * @brief Reads a HTTP header string and converts it to the header struct
 *
 * TODO: Trim trailing whitespace for header.value
 * 
 * @param str Input string to be read from
 * @param header HTTP header struct to be written to
 * @return size_t Bytes read if positive, otherwise error
 */
size_t etch_header_from_string(const char *str, EtchHeader *header);

/**
 * @brief Creates a HTTP header struct from name and value strings
 * 
 * @param name Field name of the header
 * @param value Content of the header
 * @return EtchHeader HTTP header struct
 */
EtchHeader etch_header_new(const char *name, const char *value);

/**
 * @brief Frees the memory held by the HTTP header struct
 * 
 * @param header HTTP header struct 
 */
void etch_header_free(EtchHeader header);

/**
 * @brief Frees the memory held by an array of HTTP headers
 * 
 * @param headers Array of headers 
 * @param length Lenghth of the array
 */
void etch_headers_free(EtchHeader *headers, size_t length);

#endif /* __ETCH_HTTP_HEADER_H__ */
