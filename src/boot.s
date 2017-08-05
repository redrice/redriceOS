	xref		_main
	xref		memory_init
	xref		bss_clear
	global		memory_configured

CARTMAGIC equ $fa52235f

	code

entry_rom:

	dc.l		CARTMAGIC

	move		#$2700,sr	; supervisor mode

	reset

	movea.l		#$020000,sp	; temporary stack location at the end
					; of first 128kiB block, should work
					; no matter the physical mem config

	jmp		memory_init
memory_configured:

	movea.l		_phystop,sp	; set stack pointer to the end of RAM
	move.l		_phystop,d6	; save phystop in d6, survive bss_clear

	jsr		bss_clear	; zero out bss

	move.l		d6,_phystop	; restore phystop value

	jsr		_main		; jump into C kernel code

	section		"romend",code

	dc.w		$55AA

; vim: set ft=asm68k:

