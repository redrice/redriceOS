#include <stdint.h>
#include <stddef.h>
#include <string.h>

void
memcpy(__reg("a0") void *dst, __reg("a1") void *src, __reg("d0") size_t n)
{
	uint8_t *psrc = (uint8_t *) src;
	uint8_t *pdst = (uint8_t *) dst;
	size_t i;
 
	for (i = 0; i < n; i++)
		pdst[i] = psrc[i];
}

