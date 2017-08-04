#include <stdio.h>

#include "fb.h"
#include "fbterm.h"
#include "con.h"

uint32_t phystop;

#pragma dontwarn 121
void
main(void)
{
	con_init();

	printf("redriceOS booting...\n");
	printf("%u kB memory installed\n", phystop / 1024);

	while (1) {}
}

