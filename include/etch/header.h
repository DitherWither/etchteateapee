#ifndef __ETCH_HEADER_H__
#define __ETCH_HEADER_H__

#include <stddef.h>

typedef struct EtchHeader {
        char *name;
        char *value;
} EtchHeader;

// returned value to be freed by caller
char *etch_header_to_string(EtchHeader header);
// Body used for content-length
char *etch_headers_to_string(EtchHeader header[], size_t headers_count,
                             char *body);

size_t etch_header_from_string(const char *str, EtchHeader *header);

void etch_header_free(EtchHeader header);
void etch_headers_free(EtchHeader *headers, size_t length);

#endif /* __ETCH_HEADER_H__ */
