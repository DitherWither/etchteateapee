#ifndef __ETCH_CORE_UTILS_H__
#define __ETCH_CORE_UTILS_H__
#include <stdarg.h>

#ifndef _GNU_SOURCE
int vasprintf(char **strp, const char *fmt, va_list ap);
int asprintf(char **strp, const char *fmt, ...);
#endif

/*  casprintf: print to allocated or reallocated string */
int vcasprintf(char **strp, const char *fmt, va_list ap);
int casprintf(char **strp, const char *fmt, ...);

#endif /* __ETCH_CORE_UTILS_H__ */
