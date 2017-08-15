#include <stdio.h>

#include "bitop.h"
#include "fb.h"
#include "fbterm.h"
#include "con.h"
#include "exception.h"
#include "mfp.h"

uint32_t phystop;

#pragma dontwarn 121
void
main(void)
{
	con_init();

	printf("redriceOS booting...\n");
	printf("%u KiB memory installed\n", phystop / 1024);

	exception_init();

	printf("MFP GPIO: %x\n", mfp_register_read(MFP_GPDR));

	/* cuase bus error */
	uint8_t *a;
	a = 0;
	*a = 2;

	while (1) {}
}
#pragma popwarn

