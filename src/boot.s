	xref		_main

	code

entry_rom:
	bra.s		.1
	dc.w		$0000
	dc.l		$fc0008

	movea.l		#$00000400,sp	; set stack pointer

	jsr		_main		; jump into C kernel code

.1	nop
	jmp		.1


	section		"romend",code

	dc.w		$55AA

; vim: set ft=asm68k:

