#include <stdlib.h>
#include <stdio.h>

#include "systimer.h"

#include "mfp.h"

__interrupt void
systimer_tick(void)
{
	mfp_interrupt_stat_increment(MFP_ST_INT_TIMERA);
}

void
systimer_init(void)
{
	mfp_timer_handler_set(MFP_TIMERA, systimer_tick);

	mfp_timer_setup(MFP_TIMERA, MFP_TCR_DELAY_P100, 245);

	mfp_interrupt_enable(MFP_ST_INT_TIMERA);

	printf("systimer: frequency %u Hz\n", mfp_timer_frequency(MFP_TIMERA));
}

