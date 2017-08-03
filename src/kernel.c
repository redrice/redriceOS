#include <stdio.h>

#include "fb.h"
#include "fbterm.h"
#include "con.h"

uint32_t phystop;

#pragma align(256)
static char *framebuffer[320];
#pragma align()

#pragma dontwarn 121
void
main(void)
{
	con_init();

	printf("redriceOS booting...\n");
	printf("%d kB memory installed\n", phystop / 1024);
	printf("framebuffer alignment: %x\n", (int)framebuffer & 0xFF);

	while (1) {}
}

