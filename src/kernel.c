#include <stdio.h>
#include <stddef.h>

#include "bit.h"
#include "fb.h"
#include "fbterm.h"
#include "con.h"
#include "exception.h"
#include "mfp.h"

size_t phystop;
size_t heapstart;
size_t heapsize;

#pragma dontwarn 121
void
main(void)
{
	con_init();

	printf("redriceOS booting...\n");
	heapsize = phystop - heapstart - 0x2000;  /* leave some for stack */
	printf("%u KiB memory installed (heap at 0x%06x, %u KiB available)\n", 
	    phystop / 1024, heapstart, heapsize / 1024);

	exception_init();
	mfp_init();

	/* ktest_acia(); */

	while (1) {}
}
#pragma popwarn

