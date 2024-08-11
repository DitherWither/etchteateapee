#include <etch/http/header.h>
#include <etch/core/debug.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/_types/_null.h>

char *etch_header_to_string(EtchHeader header)
{
        // seperator is two characters, plus null terminator, plus \r\n
        size_t str_length = strlen(header.name) + strlen(header.value) + 5;

        char *buf = malloc(str_length * sizeof(char));

        sprintf(buf, "%s: %s\r\n", header.name, header.value);

        return buf;
}

char *etch_headers_to_string(EtchHeader headers[], size_t headers_count,
                             const char *body)
{
        int body_length = strlen(body);
        char length_buf[16];
        snprintf(length_buf, 16, "%d", body_length);
        EtchHeader length_header = { 0 };
        length_header.name = "Content-Length";
        length_header.value = length_buf;

        size_t total_length = 3; // null terminator + newline
        total_length +=
                strlen(length_header.name) + strlen(length_header.value) + 4;

        // Calculate the buffer length
        for (size_t i = 0; i < headers_count; i++)
                total_length +=
                        strlen(headers[i].name) + strlen(headers[i].value) + 4;

        char *buf = malloc(total_length * sizeof(char));
        size_t bytes_written = 0;

        bytes_written += sprintf(buf, "%s: %s\r\n", length_header.name,
                                 length_header.value);

        for (size_t i = 0; i < headers_count; i++)
                bytes_written += sprintf(buf + bytes_written, "%s: %s\r\n",
                                         headers[i].name, headers[i].value);

        sprintf(buf + bytes_written, "\r\n");

        return buf;
}

size_t etch_header_from_string(const char *str, EtchHeader *header)
{
        if (str[0] == '\0') {
                return -1;
        }

        if (str[0] == '\r' && str[1] == '\n') {
                return -1;
        }

        char *colon_pos = strchr(str, ':');
        if (colon_pos == NULL)
                return -1;

        // Read till `:`
        size_t name_len = colon_pos - str;
        header->name = malloc(name_len + 1);
        memcpy(header->name, str, name_len);

        header->name[name_len + 1] = '\0';

        // Trim whitespace
        char *cur = colon_pos + 1;
        while (*cur == ' ')
                cur++;

        // Read till \r
        char *cr_pos = strchr(cur, '\r');
        bool is_end = false;
        if (cr_pos == NULL) {
                // Read rest of the string
                cr_pos = strchr(cur, '\0');
                is_end = true;
        }
        size_t value_len = cr_pos - cur;
        header->value = malloc(value_len + 1);
        memcpy(header->value, cur, value_len);
        header->value[value_len + 1] = '\0';

        size_t bytes_read = cr_pos - str + 2; // +1 for newline
        if (is_end)
                bytes_read -= 2;

        if (!is_end && *(cr_pos + 2) == '\r' && *(cr_pos + 3) == '\n') {
                bytes_read += 2;
        }

        return bytes_read;
}

EtchHeader etch_header_new(const char *name, const char *value)
{
        EtchHeader header = { 0 };

        header.name = malloc(strlen(name) + 1);
        strcpy(header.name, name);

        header.value = malloc(strlen(value) + 1);
        strcpy(header.value, value);

        return header;
}

void etch_header_free(EtchHeader header)
{
        free(header.name);
        free(header.value);
}

void etch_headers_free(EtchHeader *headers, size_t length)
{
        for (size_t i = 0; i < length; i++) {
                etch_header_free(headers[i]);
        }
        free(headers);
}