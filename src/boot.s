	xref		_main

	code

entry_rom:
	bra.s		.1
	dc.w		$0000
	dc.l		$fc0008

	move		#$2700,sr	; supervisor mode

	reset

	movea.l		#$00001000,sp	; set stack pointer

	; do memory init first, before going to C code

	jsr		_main		; jump into C kernel code

.1	nop
	jmp		.1


	section		"romend",code

	dc.w		$55AA

; vim: set ft=asm68k:

