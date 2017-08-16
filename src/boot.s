	xref		_main
	xref		memory_init
	xref		bss_clear
	xref		data_to_ram
	global		memory_configured

CARTMAGIC equ $fa52235f

	code

entry_rom:

	dc.l		CARTMAGIC

	move		#$2700,sr	; supervisor mode

	reset

	jmp		memory_init
memory_configured:

	movea.l		_phystop,sp	; set stack pointer to the end of RAM
	move.l		_phystop,d6	; save phystop in d6, survive bss_clear

	jsr		bss_clear	; zero out bss
	jsr		data_to_ram	; copy data section to ram

	move.l		d6,_phystop	; restore phystop value

	jsr		_main		; jump into C kernel code

	section		"romend",code

	dc.w		$55AA

; vim: set ft=asm68k:

