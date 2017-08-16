#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

uint16_t a = 1;
uint8_t b = 2;
uint16_t c = 3;

void
ktest_malloc_basic()
{
	void *d;
	d = (void *) malloc(16);
	printf("d at %p\n", d);
	memcpy(d, (void *)0x810, 16);
	free(d);
}

void
ktest_data_section()
{
	printf("a %x b %x c %x\n", a, b, c);
        a = 4; b = 5; c = 6;
        printf("a %x b %x c %x\n", a, b, c);	
}

void
ktest_bus_error()
{
	uint8_t *a;
	a = 0;
	*a = 2;
}

