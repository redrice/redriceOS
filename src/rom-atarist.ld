MEMORY {
	ram: org=0x400, len=0x3fc00
	rom: org=0xfc0000, len=0x3ffe
	romend: org=0xfc3ffe, len=0x2
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
}

