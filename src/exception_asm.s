	global _exception_handler_bus_error
	global _exception_handler_unhandled

	xref _crash_exnum

EX_BUS_ERROR equ $2
EX_UNHANDLED equ $ffff

	code

_exception_handler_bus_error:
	move.w		#EX_BUS_ERROR,_crash_exnum
	bra		_exception_save_regs

_exception_handler_unhandled:
	move.w		#EX_UNHANDLED,_crash_exnum	

_exception_save_regs:
	move.l		d0,_crash_d0;
	move.l		d1,_crash_d1;
	move.l		d2,_crash_d2;
	move.l		d3,_crash_d3;
	move.l		d4,_crash_d4;
	move.l		d4,_crash_d5;
	move.l		d6,_crash_d6;
	move.l		d7,_crash_d7;

	move.l		a0,_crash_a0;
	move.l		a1,_crash_a1;
	move.l		a2,_crash_a2;
	move.l		a3,_crash_a3;
	move.l		a4,_crash_a4;
	move.l		a4,_crash_a5;
	move.l		a6,_crash_a6;
	move.l		a7,_crash_a7;

	; huge XXX
	movea.l         #$300000,sp 

	jsr		_exception_dump_regs


; vim: set ft=asm68k:
