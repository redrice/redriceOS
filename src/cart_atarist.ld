MEMORY {
	vectorsram: org=0x0, len=0x380
	svram: org=0x380, len=0x480
	/* addresses below 0x800 are only accessible in supervisor mode */
	fbram: org=0x800, len=0x8000
	ram: org=0x8800, len=0x378000 /* up to 4MB */

	rom: org=0xFA0000, len=0x1FFFE
	romend: org=0xFBFFFE, len=0x2
}

SECTIONS {

	/* These things all go into ROM. */

	.text: {
		*(CODE)
	} >rom

	/*
	 * Data section will be outputted into ROM, but copied during boot into 
	 * RAM, see data_to_ram routine in memory.s.
	 */
	__data_rom_start = .;
	.data: {
		__data_start = .;
		. = ALIGN(2);
		*(DATA)
		. = ALIGN(2);
		__data_end = .;
	} >ram AT>rom

	/*
	.debug_aranges  : { *(.debug_aranges) } >rom
	.debug_pubnames : { *(.debug_pubnames) } >rom
	.debug_info: { *(.debug_info) } >rom
	.debug_abbrev: { *(.debug_abbrev) } >rom
	.debug_line: { *(.debug_line) } >rom
	.debug_frame: { *(.debug_frame) } >rom
	.debug_str: { *(.debug_str) } >rom
	.debug_loc: { *(.debug_loc) } >rom
	.debug_macinfo: { *(.debug_macinfo) } >rom
	*/

	.romend: {
		*(romend)
	} > romend

	/* RAM starts below. */

	.svram (NOLOAD): {
		*(svram)
	} > svram

	.fbram (NOLOAD): {
		*(fbram)
	} > fbram

	.bss (NOLOAD): {
		__bss_start = .;
		*(BSS)
		__bss_end = ALIGN(2);
	} > ram

        __bss_len = __bss_end - __bss_start;
	__data_len = __data_end - __data_start;

	__heap = .;
}

