#include <stdio.h>
#include <stdint.h>

#include "acia.h"
#include "con.h"
#include "exception.h"
#include "hardware_atarist.h"
#include "ikbd.h"
#include "ipl.h"
#include "mfp.h"

const struct con_in_def con_in_ikbd = {
	"ikbd", ikbd_getc, ikbd_init
};

//const uint8_t ikbd_codes = {
//};

struct acia_state as;

/* XXX */
uint8_t keycode;
uint8_t keycode_ready = false;

__interrupt void
ikbd_irq_handler_mcu(void)
{
	keycode = acia_data_read(&as);
	keycode_ready = true;

	mfp_interrupt_stat_increment(MFP_ST_INT_ACIA);
}

__interrupt void
ikbd_irq_handler_console(void)
{
	uint8_t r;

	r = acia_data_read(&as);

	if (!(r & 0x80)) {
		keycode = r;
		keycode_ready = true;
	}

	mfp_interrupt_stat_increment(MFP_ST_INT_ACIA);
}

void
ikbd_init()
{
	uint8_t ikbd_ver;

	as.base = ACIA_KBD_BASE;

	exception_handler_install(exception_vec_to_off(MFP_ST_VECTOR +
	    MFP_ST_INT_ACIA), ikbd_irq_handler_mcu);

	// XXX
	uint8_t ipl = 3;
	ipl_set(&ipl);

	acia_configure(&as, ACIA_CR_DIV_64 | (ACIA_CR_WORDSEL_8B_1SB << ACIA_CR_WORDSEL_SHIFT) | ACIA_CR_RECVIRQ);

	mfp_interrupt_enable(MFP_ST_INT_ACIA);

	acia_data_write(&as, 0x80);
	acia_data_write(&as, 0x01);
	ikbd_ver = ikbd_getc();

	acia_data_write(&as, 0x12);

	exception_handler_install(exception_vec_to_off(MFP_ST_VECTOR +
	    MFP_ST_INT_ACIA), ikbd_irq_handler_console);

	printf("ikbd: controller version %x\n", ikbd_ver);
}

/*
 * Returns ASCII character representation of a pressed key. Blocking.
 *
 * Or rather, should return, currently returns a raw IKBD key code.
 */
uint8_t
ikbd_getc()
{
	/* XXX: add readahead */
	while (keycode_ready != true)
		;; /*
		    * Should it bail out with error, or should it wait
		    * indefinitely?
		    */

	keycode_ready = false;
	return keycode;
}

