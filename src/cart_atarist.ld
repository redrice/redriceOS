MEMORY {
	vectorsram: org=0x0, len=0x400
	/* XXX: addresses below 0x800 are only accessible in supervisor mode */
	fbram: org=0x400, len=0x8000
	ram: org=0x8400, len=0x3F7C00 /* up to 4MB */

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

	.fbram (NOLOAD): {
		*(fbram)
	} > fbram

	.bss (NOLOAD): {
		__bss_start = .;
		*(BSS)
		__bss_end = ALIGN(2);
	} > ram

        __bss_len = __bss_end - __bss_start;
}

