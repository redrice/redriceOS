#ifndef _STDIO_H_
#define _STDIO_H_

#include <stdarg.h>

extern int vprintf(const char *, va_list);
extern int printf(const char *, ...);

#endif /* _STDIO_H_ */

