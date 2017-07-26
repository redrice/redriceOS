MEMORY {
	vectorsram: org=0x0, len=0x400
	ram: org=0x400, len=0x3FFC00

	rom: org=0xfc0000, len=0x3FFE
	romend: org=0xFC3FFE, len=0x2
}

SECTIONS {

	.text: {
		*(CODE)
	} >rom

	.data: {
		. = ALIGN(2);
		*(DATA)
		. = ALIGN(2);
	} >rom

	.romend: {
		*(romend)
	} > romend

	.bss (NOLOAD): {
		__bss_start = .;
		*(BSS)
		__bss_end = ALIGN(2);
	} > ram
}

