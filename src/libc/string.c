#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>

void
memcpy(__reg("a0") void *dst, __reg("a1") void *src, __reg("d0") size_t n)
{
	uint8_t *psrc = (uint8_t *) src;
	uint8_t *pdst = (uint8_t *) dst;
	size_t i;
 
	for (i = 0; i < n; i++)
		pdst[i] = psrc[i];
}

void
memmove(void *dst, const void *src, size_t len)
{
	int i;

	char *csrc = (char *)src;
	char *cdest = (char *)dst;

	char *temp = malloc(len);

	for (i = 0; i < len; i++)
		temp[i] = csrc[i];

	for (i = 0; i < len; i++)
		cdest[i] = temp[i];

	free(temp);
}

void *
memset(void* s, int c, size_t sz) {

	uint8_t* p = (uint8_t *) s;

	uint8_t x = c & 0xff;

	while (sz--)
		*p++ = x;

	return s;
}

size_t
strlen(const char *str)
{
	const char *s;
	for (s = str; *s; ++s) {}
		return(s - str);
}

char *
strncat(char *dest, const char *src, size_t n)
{
	char *ret = dest;
	while (*dest)
		dest++;
	while (n--)
		if (!(*dest++ = *src++))
			return ret;
	*dest = 0;
	return ret;
}

int
strcmp(const char* str1, const char* str2)
{
	while(*str1 && (*str1 == *str2)) {
		str1++;
		str2++;
	}

	return *(const unsigned char*)str1 - *(const unsigned char*)str2;
}

char *
strncpy(char *dst, const char *src, size_t n)
{
	int i;
	char *t;

	t = dst;
	for (i = 0; i < n; i++)
		*dst++ = *src++;

	return t;
}

