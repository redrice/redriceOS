#include <stdio.h>

#include "con.h"
#include "fb.h"
#include "fbterm.h"
#include "mfp.h"
#include "serial.h"

extern struct con_dev_def con_dev_mfp;
extern struct con_dev_def con_dev_fbterm;

struct con_dev_def *console;

void
con_init()
{
	console = &con_dev_mfp;
	/* console = &con_dev_fbterm; */

	console->init();

	printf("console: %s\n", console->name);
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

