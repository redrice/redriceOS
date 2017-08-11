#include <stdio.h>
#include <stdint.h>

#include "exception.h"

extern void exception_handler_bus_error(void) ;

struct crash_frame_g0 {
	uint16_t access_type;
	uint32_t access_addr;
	uint16_t ir;		/* instruction register */
	uint16_t sr;		/* status register */
	uint32_t pc;		/* program counter */
};

__section("svram") uint32_t crash_d0;
__section("svram") uint32_t crash_d1;
__section("svram") uint32_t crash_d2;
__section("svram") uint32_t crash_d3;
__section("svram") uint32_t crash_d4;
__section("svram") uint32_t crash_d5;
__section("svram") uint32_t crash_d6;
__section("svram") uint32_t crash_d7;
__section("svram") uint32_t crash_a0;
__section("svram") uint32_t crash_a1;
__section("svram") uint32_t crash_a2;
__section("svram") uint32_t crash_a3;
__section("svram") uint32_t crash_a4;
__section("svram") uint32_t crash_a5;
__section("svram") uint32_t crash_a6;
__section("svram") uint32_t crash_a7;

__section("svram") uint8_t crash_exnum;
__section("svram") uint8_t crash_frametype;

__section("svram") uint16_t crash_frame[7];

static uint16_t
exception_vec_to_off(uint8_t v)
{
	return v * 4;
}

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

#define EX_BUS_ERROR 2
#define EX_ADDRESS_ERROR 3
	/* override selected exceptions */
	exception_handler_install(exception_vec_to_off(EX_BUS_ERROR),
		exception_handler_bus_error);

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
exception_dump_g0(void)
{
	struct crash_frame_g0 *fptr;

	fptr = (struct crash_frame_g0 *) &crash_frame;

	printf("PC %8x AA %8x OP %8x IR %8x SR %x", 
	    fptr->pc, fptr->access_addr, fptr->access_type, fptr->ir, fptr->sr);
}

void
exception_dump_regs(void)
{

	printf("Exception %x\n", crash_exnum);
	printf("D0 %8x D1 %8x D2 %8x D3 %8x\n",
	    crash_d0, crash_d1, crash_d2, crash_d3);
	printf("D4 %8x D5 %8x D6 %8x D7 %8x\n",
	    crash_d4, crash_d5, crash_d6, crash_d7);
	printf("A0 %8x A1 %8x A2 %8x A3 %8x\n",
	    crash_a0, crash_a1, crash_a2, crash_a3);
	printf("A4 %8x A5 %8x A6 %8x A7 %8x\n",
	    crash_a4, crash_a5, crash_a6, crash_a7);

	if ((crash_exnum == EX_BUS_ERROR) ||
	    (crash_exnum == EX_ADDRESS_ERROR))
		exception_dump_g0();
	// else g1/g2

	while (1) {}

}

