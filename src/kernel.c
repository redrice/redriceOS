#include <stdio.h>
#include <stddef.h>
#include <string.h>

#include "bit.h"
#include "fb.h"
#include "fbterm.h"
#include "con.h"
#include "exception.h"
#include "mfp.h"

size_t phystop;
size_t heapstart;
size_t heapsize;

uint16_t a = 1;
uint8_t b = 2;
uint16_t c = 3;

#pragma dontwarn 121
void
main(void)
{
	uint8_t *d;
	con_init();

	printf("redriceOS booting...\n");

	heapsize = phystop - heapstart - 0x2000;  /* leave some for stack */
	printf("%u KiB memory installed (heap at %x, %u KiB available)\n", 
	    phystop / 1024, heapstart, heapsize / 1024);

	exception_init();

	/* memory allocation and copying test */
	d = (uint8_t *) umm_malloc(16);
	printf("d at %p\n", d);
	memcpy(d, (void *)0x810, 16);

	/* data section test */
	printf("a %x b %x c %x\n", a, b, c);
	a = 4; b = 5; c = 6;
	printf("a %x b %x c %x\n", a, b, c);

	/* cause bus error */
	uint8_t *a;
	a = 0;
	*a = 2;

	while (1) {}
}
#pragma popwarn

