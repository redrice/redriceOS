#include <stdio.h>
#include <stdint.h>

#include "exception.h"

void
exception_init(void) 
{
	uint16_t off;

	/* first init all vectors with unhandled exception handler */
	off = 0x8;
	while(off < 0x380) {
		exception_handler_install(off, exception_handler_unhandled);
		off += 0x4;
	}

}

void
exception_handler_install(uint16_t offset, void(*handler)(void) )
{
	/* XXX: should define uptr-something type for this purpose */
	uint32_t *vector;
       
	vector = (uint32_t *) offset;

	/* printf("installing handler %p at offset %x\n", handler , offset); */

	*vector = (uint32_t) handler;
		
}

void
exception_handler_unhandled(void)
{
	printf("lulz, unhandled exception\n");

	while (1) {}
}

