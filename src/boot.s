	xref		_main
	xref		memory_init
	xref		bss_clear
	global		memory_configured

	code

entry_rom:
	bra.s		.1
	dc.w		$0000
	dc.l		$fc0008

.1:
	move		#$2700,sr	; supervisor mode

	reset

	movea.l		#$020000,sp	; temporary stack location at the end
					; of first 128kiB block, should work
					; no matter the physical mem config

	jmp		memory_init
memory_configured:

	movea.l		_phystop,sp	; set stack pointer to the end of RAM

	jsr		bss_clear	; zero out bss

	jsr		_main		; jump into C kernel code

	section		"romend",code

	dc.w		$55AA

; vim: set ft=asm68k:

