	global _exception_handler_bus_error
	global _exception_handler_address_error
	global _exception_handler_unhandled

	xref _phystop
	xref _crash_exnum
	xref _crash_d0
	xref _crash_a0
	xref _crash_frame

EX_BUS_ERROR equ $2
EX_ADDRESS_ERROR equ $3
EX_UNHANDLED equ $ff

	code

_exception_handler_bus_error:
	move.b		#EX_BUS_ERROR,_crash_exnum
	bra		_exception_handler_fatal
_exception_handler_address_error:
	move.b		#EX_ADDRESS_ERROR,_crash_exnum
	bra		_exception_handler_fatal

_exception_handler_unhandled:
	move.b		#EX_UNHANDLED,_crash_exnum

; save register information and stack frame upon encountering fatal exception
_exception_handler_fatal:
	move		#$2700,sr	; supervisor mode, interrupts disabled
_exception_save_regs:
	; save all d regs to _crash_d0 to _crash_d7
	movem.l		d0-d7,_crash_d0
	; save all a regs to _crash_a0 to _crash_a7
	movem.l		a0-a7,_crash_a0

	; save exception stack frame, up to 7x 16-bit words
	movem.w		(sp),d0-d6
	movem.w		d0-d6,_crash_frame

	; will not resume anyway, so reset the stack pointer
	movea.l         _phystop,sp

	jsr		_exception_dump_regs

; vim: set ft=asm68k:

