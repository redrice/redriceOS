#include <stdio.h>

#include "con.h"
#include "fb.h"
#include "fbterm.h"
#include "mfp.h"
#include "serial.h"
#include "msgbuf.h"

extern struct con_dev_def con_dev_mfp;
extern struct con_dev_def con_dev_fbterm;

struct con_dev_def *console = 0;

void
con_init()
{
	/* console = &con_dev_mfp; */
	console = &con_dev_fbterm;

	fb_init();

	console->init();

	msgbuf_print(console);

	printf("console: %s\n", console->name);
}

void
con_putc(uint8_t c)
{
	/*
	 * Things are saved to a buffer that can be replayed after console
	 * init/change or using a command.
	 */
	msgbuf_putc(c);

	if (console != 0)
		console->putc(c);
}

