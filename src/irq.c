#include <stdio.h>

__interrupt void
irq_handler_vbl(void)
{
	/* do things at vbl */
}

__interrupt void
irq_handler_mfp(void)
{
	/* do things when mfp interrupts */
}

