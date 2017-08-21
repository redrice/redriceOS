#include <stdio.h>
#include <stddef.h>

#include "bit.h"
#include "fb.h"
#include "fbterm.h"
#include "con.h"
#include "exception.h"
#include "mfp.h"
#include "msgbuf.h"

size_t phystop;
size_t heapstart;
size_t heapsize;

#pragma dontwarn 121
void
main(void)
{
	heapsize = phystop - heapstart - 0x2000;  /* leave some for stack */

	msgbuf_init();

	printf("redriceOS booting...\n");
	printf("%u KiB memory installed (heap at 0x%06x, size %u KiB)\n",
	    phystop / 1024, heapstart, heapsize / 1024);

	exception_init();
	con_init();

	mfp_init();

	/* ktest_acia(); */

	while (1) {}
}
#pragma popwarn

