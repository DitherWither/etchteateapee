#include <etch/request.h>
#include <string.h>

const char *METHODS[] = { "OPTIONS", "GET",    "HEAD",  "POST",
                          "PUT",     "DELETE", "TRACE", "CONNECT"};

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