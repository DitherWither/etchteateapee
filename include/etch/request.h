#ifndef __ETCH_REQUEST_H__
#define __ETCH_REQUEST_H__

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

const char *etch_method_to_string(EtchMethod method);

#endif /* __ETCH_REQUEST_H__ */
