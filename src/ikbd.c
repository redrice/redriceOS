#include <stdio.h>
#include <stdint.h>

#include "acia.h"
#include "con.h"
#include "exception.h"
#include "hardware_atarist.h"
#include "ikbd.h"
#include "ipl.h"
#include "mfp.h"
#include "keymap.h"

const struct con_in_def con_in_ikbd = {
	"ikbd", ikbd_getc, ikbd_init
};

struct acia_state as;

/* XXX */
static volatile uint8_t keycode;
static volatile uint8_t keycode_ready = false;

static bool shift_active = false;
static bool alt_active = false;

extern const uint8_t keymap_ikbd[];

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
	uint8_t r, c;

	mfp_interrupt_stat_increment(MFP_ST_INT_ACIA);

	r = acia_data_read(&as);

	if ((r == IKBD_LSHIFT) || (r == IKBD_RSHIFT)) {
		shift_active = true;
		return;
	}
	if (r == (IKBD_LSHIFT + IKBD_RELEASE) ||
	    (r == (IKBD_RSHIFT + IKBD_RELEASE))) {
		shift_active = false;
		return;
	}

	if (r == (IKBD_ALT)) {
		alt_active = true;
		return;
	}
	if (r == (IKBD_ALT + IKBD_RELEASE)) {
		alt_active = false;
		return;
	}


	/* Get machine independent key code from keymap. */
	c = keymap_ikbd[r];

	// XXX
	if (r & 0x80)
		return;

	keycode = c;
	keycode_ready = true;
}

void
ikbd_init()
{
	uint8_t ikbd_ver;

	as.base = ACIA_KBD_BASE;

	exception_handler_install(exception_vec_to_off(MFP_ST_VECTOR +
	    MFP_ST_INT_ACIA), ikbd_irq_handler_mcu);

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

