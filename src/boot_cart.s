	xref		boot_common	

CARTMAGIC equ $fa52235f

	section		"boot",code

entry_rom:
	; ID used by TOS to jump early into code on cartridge.
	dc.l		CARTMAGIC
	jmp		boot_common

	section		"romend",code

	dc.w		$55AA

; vim: set ft=asm68k:

