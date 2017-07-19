MEMORY {
	ram: org=0x400, len=0x3fc00
	rom: org=0xe00000, len=0x40000
}

SECTIONS {

	.text: {
		*(CODE)
	} > rom

	.data: {
		. = ALIGN(2);
		*(DATA)
		. = ALIGN(2);
	} > rom

;	.bss (NOLOAD): {
;		__bss_start = .;
;		*(BSS)
;		__bss_end = ALIGN(2);
;	} > ram

}
