#include <stdio.h>

__interrupt void
irq_handler_vbl(void)
{
	/* do things at vbl */
}

__interrupt void
irq_handler_mfp(void)
{
	printf("IPL 6 vector this should never happen\n");
	/* do things when mfp interrupts */
}

