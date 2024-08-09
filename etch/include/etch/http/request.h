#ifndef __ETCH_HTTP_REQUEST_H__
#define __ETCH_HTTP_REQUEST_H__

#include <etch/http/header.h>

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

typedef struct EtchRequest {
        EtchMethod method;
        char *path;
        EtchHeader *headers;
        size_t headers_count;
        char *body;
} EtchRequest;

const char *etch_method_to_string(EtchMethod method);
EtchMethod etch_method_from_string(const char *str);

EtchRequest etch_request_from_string(const char *str);
void etch_free_request(EtchRequest request);

#endif /* __ETCH_HTTP_REQUEST_H__ */
