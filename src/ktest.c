#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

/* for ktest_data_section */
uint16_t a = 1;
uint8_t b = 2;
uint16_t c = 3;

void
ktest_malloc_basic()
{
	void *d;
	d = (void *) malloc(16);
	printf("d at %p\n", d);
	memcpy(d, (void *)0x810, 16);
	free(d);
}

void
ktest_data_section()
{
	printf("a %x b %x c %x\n", a, b, c);
        a = 4; b = 5; c = 6;
        printf("a %x b %x c %x\n", a, b, c);	
}

void
ktest_bus_error()
{
	uint8_t *a;
	a = 0;
	*a = 2;
}

void
ktest_console_print20()
{
	int i;
	for(i = 0; i < 20;  i++)
		printf("aaaaa\n");
}

void
__interrupt void
ktest_irq_handler_timera(void)
{
//      printf("nig %x %x \n", mfp_register_read(MFP_TADR), mfp_register_read(MFP_IPRA));
        mfp_interrupt_stat_increment(MFP_ST_INT_TIMERA);
}

kovid
ktest_timera(void)
{
	uint8_t ipl = 3;
	ipl_set(&ipl);

	mfp_init();
	mfp_interrupt_enable(MFP_ST_INT_TIMERA);
	mfp_timer_handler_set(MFP_TIMERA, irq_handler_timera);
	mfp_timer_setup(MFP_TIMERA, MFP_TCR_DELAY_P16, 255);

	printf("test\n");
        printf("test\n");
        printf("test\n");
        printf("test\n");
        printf("test\n");
        printf("test\n");
        printf("test\n");
        printf("test\n");
        mfp_timer_setup(MFP_TIMERA, 0, 0);
        mfp_interrupt_stat_print();
}

