#include <stdio.h>

#include "fb.h"
#include "fbterm.h"
#include "con.h"
#include "exception.h"

uint32_t phystop;

#pragma dontwarn 121
void
main(void)
{
	con_init();

	printf("redriceOS booting...\n");
	printf("%u KiB memory installed\n", phystop / 1024);

	exception_init();

	while (1) {}
}

