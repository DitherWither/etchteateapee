#include "connection.h"
#include <etch/response.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct etch_response_raw handler(char *buffer, size_t len)
{
        struct etch_response_raw response_raw = { 0 };
        int bytes_written = 0;
        response_raw.bytes = malloc(256 * sizeof(char));

        bytes_written = snprintf(response_raw.bytes, 256 - response_raw.len, "Hello, World");
        if (bytes_written == EOF) {
                perror("failed to write to buffer");
                return response_raw;
        }
        response_raw.len += bytes_written;
        return response_raw;
}

int32_t main()
{
        etch_serve(8080, handler);
        return 0;
}
