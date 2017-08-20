#include "con.h"
#include "fb.h"
#include "fbterm.h"
#include "mfp.h"
#include "serial.h"

extern struct con_dev_def con_dev_mfp;

struct con_dev_def *console;

void
con_init()
{
	/*
	fbterm_init();	
	console.putc = &fbterm_putc;
	*/

	console = &con_dev_mfp;
}

void
con_putc(uint8_t c)
{
	/*
	 * Things should be saved to a buffer that could be replayed
	 * after console init/change or using a command.
	 */
	console->putc(c);
}

