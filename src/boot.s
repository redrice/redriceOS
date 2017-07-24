	xref		_main

	code

entry_rom:
	bra.s		.1
	dc.w		$0000
	dc.l		$fc0008

	move		#$2700,sr	; supervisor mode

	reset

	move.b		#$A,$ff8001	; hard code memory ctrl to 4MB

	movea.l		#$00001000,sp	; set stack pointer

	jsr		_main		; jump into C kernel code

.1	nop
	jmp		.1


	section		"romend",code

	dc.w		$55AA

; vim: set ft=asm68k:

