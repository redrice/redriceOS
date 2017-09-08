#ifndef _STRING_H_
#define _STRING_H_

void memcpy(__reg("a0") void *, __reg("a1") void *, __reg("d0") size_t);
void memmove(void *, const void *, size_t);
void * memset(void*, int, size_t);

char * strncat(char *, const char *, size_t);
int strcmp(const char*, const char*);
size_t strlen(const char *);
char *strncpy(char *, const char *, size_t);

#endif /* _STRING_H_ */

