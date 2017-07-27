	xref		_main
	xref		memory_init
	global		memory_configured

	code

entry_rom:
	bra.s		.1
	dc.w		$0000
	dc.l		$fc0008

.1:
	move		#$2700,sr	; supervisor mode

	reset

	jmp		memory_init
memory_configured:

	movea.l		#$400000,sp	; set stack pointer to the end of RAM
					; XXX: hard coded to 4MB

	jsr		_main		; jump into C kernel code


	section		"romend",code

	dc.w		$55AA

; vim: set ft=asm68k:

