#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#include "exception.h"
#include "hardware_atarist.h"
#include "acia.h"
#include "ipl.h"
#include "mfp.h"
#include "con.h"
#include "msgbuf.h"

extern struct con_dev_def con_dev_fbterm;

/* for ktest_data_section */
uint16_t a = 1;
uint8_t b = 2;
uint16_t c = 3;

struct acia_state as;

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


__interrupt void
ktest_irq_handler_timera(void)
{
//      printf("nig %x %x \n", mfp_register_read(MFP_TADR), mfp_register_read(MFP_IPRA));
        mfp_interrupt_stat_increment(MFP_ST_INT_TIMERA);
}

void
ktest_timera(void)
{
	uint8_t ipl = 3;
	ipl_set(&ipl);

	mfp_init();
	mfp_interrupt_enable(MFP_ST_INT_TIMERC);
	mfp_timer_handler_set(MFP_TIMERC, ktest_irq_handler_timera);
	mfp_timer_setup(MFP_TIMERC, MFP_TCR_DELAY_P200, 255);

	printf("test\n");
        printf("test\n");
        printf("test\n");
        printf("test\n");
	printf("MFP TCDR: %x\n", mfp_register_read(MFP_TCDR));
	mfp_timer_stats_print();
        printf("test\n");
        printf("test\n");
        printf("test\n");
        printf("test\n");
	mfp_timer_stop(MFP_TIMERC);
        mfp_interrupt_stat_print();
	mfp_timer_stats_print();
}

__interrupt void
ktest_irq_handler_acia(void)
{
	uint8_t code;

	code = acia_data_read(&as);
	printf("code %x\n", code);
        mfp_interrupt_stat_increment(MFP_ST_INT_ACIA);
}

void
ktest_acia()
{
	exception_handler_install(exception_vec_to_off(MFP_ST_VECTOR +
	    MFP_ST_INT_ACIA), ktest_irq_handler_acia);
	uint8_t ipl = 3;
	as.base = ACIA_KBD_BASE;
	ipl_set(&ipl);
	mfp_interrupt_enable(MFP_ST_INT_ACIA);
	acia_configure(&as, ACIA_CR_DIV_64 | (ACIA_CR_WORDSEL_8B_1SB << ACIA_CR_WORDSEL_SHIFT) | ACIA_CR_RECVIRQ);

	acia_data_write(&as, 0x80);

	printf("status: %x data: %x\n", acia_status_read(&as),
	    acia_data_read(&as));

	acia_data_write(&as, 0x01);

	printf("status: %x data: %x\n", acia_status_read(&as),
	    acia_data_read(&as));
}

void
ktest_msgbuf_print()
{
	msgbuf_print(&con_dev_fbterm);
}

