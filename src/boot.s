	xref		_main
	xref		memory_init
	xref		bss_clear
	xref		data_to_ram
	global		memory_configured
	global		boot_common

	code

boot_common:
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

; vim: set ft=asm68k:

