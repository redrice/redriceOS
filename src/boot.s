	code

entry_rom:
	bra.s		.1
	dc.w		$0000
	dc.l		$fc0008

.1	nop
	jmp		.1


	section		"romend",code

	dc.w		$55AA

; vim: set ft=asm68k:

