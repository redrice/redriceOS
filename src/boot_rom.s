	xref		boot_common	

	section		"boot",code

entry_rom:
	bra.s		jump_to_boot
	dc.w		$0000
	dc.l		jump_to_boot

jump_to_boot:
	jmp		boot_common

	section		"romend",code

	dc.w		$55AA

; vim: set ft=asm68k:

