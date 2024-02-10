#include <etch/utils.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef _GNU_SOURCE
int vasprintf(char **strp, const char *fmt, va_list ap)
{
        va_list ap1;
        int len;
        char *buffer;
        int res;

        va_copy(ap1, ap);
        len = vsnprintf(NULL, 0, fmt, ap1);

        if (len < 0)
                return len;

        va_end(ap1);
        buffer = malloc(len + 1);

        if (!buffer)
                return -1;

        res = vsnprintf(buffer, len + 1, fmt, ap);

        if (res < 0)
                free(buffer);
        else
                *strp = buffer;

        return res;
}

int asprintf(char **strp, const char *fmt, ...)
{
        int error;
        va_list ap;

        va_start(ap, fmt);
        error = vasprintf(strp, fmt, ap);
        va_end(ap);

        return error;
}
#endif

int vcasprintf(char **strp, const char *fmt, va_list ap)
{
        int ret;
        char *strp1;
        if (*strp == NULL)
                return vasprintf(strp, fmt, ap);

        ret = vasprintf(&strp1, fmt, ap); // ret = strlen(strp1) or -1
        if (ret == -1)
                return ret;
        if (ret == 0) {
                free(strp1);
                return strlen(*strp);
        }

        size_t len = strlen(*strp);
        *strp = realloc(*strp, len + ret + 1);
        memcpy((*strp) + len, strp1, ret + 1);
        free(strp1);
        return (len + ret);
}

int casprintf(char **strp, const char *fmt, ...)
{
        int ret;
        va_list ap;
        va_start(ap, fmt);
        ret = vcasprintf(strp, fmt, ap);
        va_end(ap);
        return (ret);
}