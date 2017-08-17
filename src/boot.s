	xref		_main
	xref		memory_init
	xref		bss_clear
	xref		data_to_ram
	global		memory_configured

CARTMAGIC equ $fa52235f

	code

entry_rom:
	; ID used by TOS to jump early into code on cartridge.
	dc.l		CARTMAGIC

	; Theoretically CPU should be in supervisor mode now, but 
	; someone could have performed "warm" reboot by jumping into
	; this location.
	move		#$2700,sr	; supervisor mode, interrupts disabled

	reset				; reset peripherals

	jmp		memory_init	; init the memory controller

memory_configured:
	movea.l		_phystop,sp	; set stack pointer to the end of RAM
	move.l		_phystop,d6	; save phystop in d6, survive bss_clear

	jsr		bss_clear	; zero out bss
	jsr		data_to_ram	; copy data section to ram

	move.l		d6,_phystop	; restore phystop value
	move.l		#__heap,_heapstart ; save heap start address

	jsr		_main		; jump into C kernel code

	; This section is used to mark end of ROM. Linker automatically fills
	; empty space in ROM with zeros.
	section		"romend",code

	dc.w		$55AA

; vim: set ft=asm68k:

