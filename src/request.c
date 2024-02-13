#include <etch/header.h>
#include <etch/request.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>

const char *METHODS[] = { "OPTIONS", "GET",    "HEAD",  "POST",
                          "PUT",     "DELETE", "TRACE", "CONNECT" };

#define METHODS_COUNT 8

const char *etch_method_to_string(EtchMethod method)
{
        if (method == ETCH_METHOD_UNKNOWN) {
                return NULL;
        }
        return METHODS[method];
}

EtchMethod etch_method_from_string(const char *str)
{
        for (int i = 0; i < METHODS_COUNT; i++)
                if (strcmp(METHODS[i], str) == 0)
                        return i;

        return ETCH_METHOD_UNKNOWN;
}

EtchRequest etch_request_from_string(const char *str)
{
        EtchRequest request = { 0 };

        char *method_str = 0;
        int bytes_read = 0;

        sscanf(str, "%ms %ms %*s%n", &method_str, &request.path, &bytes_read);

        if (*(str + bytes_read) == '\r')
                bytes_read++;
        if (*(str + bytes_read) == '\n')
                bytes_read++;

        
        request.method = etch_method_from_string(method_str);
        free(method_str);

        size_t headers_size = 16;
        request.headers = malloc(headers_size * sizeof(EtchHeader));

        int res;

        while ((res = etch_header_from_string(
                        str + bytes_read, &request.headers[request.headers_count])) > 0) {
                request.headers_count++;
                if (request.headers_count >= headers_size) {
                        headers_size += 16;
                        request.headers =
                                realloc(request.headers,
                                        headers_size * sizeof(EtchHeader));
                }
                bytes_read += res;
        }

        // request.headers_count += 1;

        if ((str + bytes_read)[0] == '\0') {
                request.body = NULL;
                return request;
        }
        int content_length = -1;

        for (int i = 0; i < request.headers_count - 1; i++) {
                if (strcasecmp(request.headers[i].name, "Content-Length") ==
                    0) {
                        sscanf(request.headers[i].value, "%d", &content_length);
                }
        }
        if (content_length <= 0) {
                request.body = NULL;
                return request;
        }

        request.body = malloc(strlen(str + bytes_read) + 1);
        strcpy(request.body, str + bytes_read);
        return request;
}

void etch_free_request(EtchRequest request)
{
        free(request.path);
        // etch_headers_free(request.headers, request.headers_count);
        free(request.body);
}