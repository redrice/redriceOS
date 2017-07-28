MEMORY {
	vectorsram: org=0x0, len=0x400
	ram: org=0x400, len=0x3FFC00

	rom: org=0xFA0000, len=0x1FFFE
	romend: org=0xFBFFFE, len=0x2
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

        __bss_len = __bss_end - __bss_start;
}

