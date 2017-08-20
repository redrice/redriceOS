#include "con.h"
#include "fb.h"
#include "fbterm.h"
#include "mfp.h"
#include "serial.h"

struct con_dev {
	void (*putc)(uint8_t);
};

struct con_dev console;

void
con_init()
{
	/*
	fb_init();
	fbterm_init();	
	console.putc = &fbterm_putc;
	*/
	mfp_serial_init(BAUD_19200, ASYNC_STOP1_START1, PARITY_NONE);
	console.putc = &mfp_serial_write;
}

void
con_putc(uint8_t c)
{
	/*
	 * Things should be saved to a buffer that could be replayed
	 * after console init/change or using a command.
	 */
	console.putc(c);	
}

