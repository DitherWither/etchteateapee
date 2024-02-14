#ifndef __ETCH_RESPONSE_H__
#define __ETCH_RESPONSE_H__

#include <etch/http/header.h>
#include <stddef.h>

typedef enum EtchStatusCode {
        ETCH_STATUS_CODE_CONTINUE = 100,
        ETCH_STATUS_CODE_SWITCHING_PROTOCOLS = 101,
        ETCH_STATUS_CODE_OK = 200,
        ETCH_STATUS_CODE_CREATED = 201,
        ETCH_STATUS_CODE_ACCEPTED = 202,
        ETCH_STATUS_CODE_NON_AUTHORITATIVE_INFORMATION = 203,
        ETCH_STATUS_CODE_NO_CONTENT = 204,
        ETCH_STATUS_CODE_RESET_CONTENT = 205,
        ETCH_STATUS_CODE_PARTIAL_CONTENT = 206,
        ETCH_STATUS_CODE_MULTIPLE_CHOICES = 300,
        ETCH_STATUS_CODE_MOVED_PERMANENTLY = 301,
        ETCH_STATUS_CODE_FOUND = 302,
        ETCH_STATUS_CODE_SEE_OTHER = 303,
        ETCH_STATUS_CODE_NOT_MODIFIED = 304,
        ETCH_STATUS_CODE_USE_PROXY = 305,
        ETCH_STATUS_CODE_TEMPORARY_REDIRECT = 307,
        ETCH_STATUS_CODE_BAD_REQUEST = 400,
        ETCH_STATUS_CODE_UNAUTHORIZED = 401,
        ETCH_STATUS_CODE_PAYMENT_REQUIRED = 402,
        ETCH_STATUS_CODE_FORBIDDEN = 403,
        ETCH_STATUS_CODE_NOT_FOUND = 404,
        ETCH_STATUS_CODE_METHOD_NOT_ALLOWED = 405,
        ETCH_STATUS_CODE_NOT_ACCEPTABLE = 406,
        ETCH_STATUS_CODE_PROXY_AUTHENTICATION_REQUIRED = 407,
        ETCH_STATUS_CODE_REQUEST_TIMEOUT = 408,
        ETCH_STATUS_CODE_CONFLICT = 409,
        ETCH_STATUS_CODE_GONE = 410,
        ETCH_STATUS_CODE_LENGTH_REQUIRED = 411,
        ETCH_STATUS_CODE_PRECONDITION_FAILED = 412,
        ETCH_STATUS_CODE_REQUEST_ENTITY_TOO_LARGE = 413,
        ETCH_STATUS_CODE_REQUEST_URI_TOO_LARGE = 414,
        ETCH_STATUS_CODE_UNSUPPORTED_MEDIA_TYPE = 415,
        ETCH_STATUS_CODE_REQUESTED_RANGE_NOT_SATISFIABLE = 416,
        ETCH_STATUS_CODE_EXPECTATION_FAILED = 417,
        ETCH_STATUS_CODE_INTERNAL_SERVER_ERROR = 500,
        ETCH_STATUS_CODE_NOT_IMPLEMENTED = 501,
        ETCH_STATUS_CODE_BAD_GATEWAY = 502,
        ETCH_STATUS_CODE_SERVICE_UNAVAILABLE = 503,
        ETCH_STATUS_CODE_GATEWAY_TIMEOUT = 504,
        ETCH_STATUS_CODE_HTTP_VERSION_NOT_SUPPORTED = 505
} EtchStatusCode;

const char *etch_status_code_to_string(EtchStatusCode status_code);

typedef struct EtchResponseRaw {
        char *bytes;
        size_t len;
} EtchResponseRaw;

// headers and body must be heap allocated with malloc, as free is called in destructor
typedef struct EtchResponse {
        EtchStatusCode status_code;
        EtchHeader *headers;
        size_t headers_count;
        char *body;
} EtchResponse;

EtchResponse etch_response_default();

EtchResponseRaw etch_response_serialize(EtchResponse res);

void etch_response_add_header(EtchResponse *res, const char *name,
                              const char *value);

void etch_response_free(EtchResponse res);

int etch_response_serve_file(EtchResponse *res, const char* path);

#endif /* __ETCH_RESPONSE_H__ */
