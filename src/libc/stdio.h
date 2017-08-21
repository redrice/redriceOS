#ifndef _STDIO_H_
#define _STDIO_H_

#include <stdarg.h>

int vprintf(const char *, va_list);
int printf(const char *, ...);

int printf_nobuf(const char *fmt, ...);

#endif /* _STDIO_H_ */

