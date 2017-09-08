#ifndef _STDLIB_H_
#define _STDLIB_H_

#include "../umm_malloc/umm_malloc.h"

#define malloc(_x) umm_malloc(_x)
#define free(_x) umm_free(_x)
#define calloc(_x, _y) umm_calloc(_x, _y)
#define realloc(_x, _y) umm_realloc(_x, _y)

#endif /* _STDLIB_H_ */
