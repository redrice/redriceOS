	global _exception_handler_bus_error
	global _exception_handler_unhandled

	xref _crash_exnum

EX_BUS_ERROR equ $2
EX_UNHANDLED equ $ff

FRAME_G0 equ $0
FRAME_G1 equ $1
FRAME_G2 equ $2

	code

_exception_handler_bus_error:
	move.b		#EX_BUS_ERROR,_crash_exnum
;	move.b set frame type
	bra		_exception_save_regs

_exception_handler_unhandled:
	move.b		#EX_UNHANDLED,_crash_exnum

_exception_save_regs:
	; save all d regs to _crash_d0 to _crash_d7
	movem.l		d0-d7,_crash_d0
	movem.l		a0-a7,_crash_a0

	; save exception stack frame, up to 7x 16-bit words
	movem.w		(sp),d0-d6
	movem.w		d0-d6,_crash_frame

	; huge XXX
	movea.l         #$300000,sp 

	jsr		_exception_dump_regs

; vim: set ft=asm68k:
