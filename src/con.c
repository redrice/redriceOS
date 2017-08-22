#include <stdio.h>
#include <stdbool.h>

#include "con.h"
#include "fb.h"
#include "fbterm.h"
#include "mfp.h"
#include "serial.h"
#include "msgbuf.h"

extern struct con_out_def con_out_mfp;
extern struct con_out_def con_out_fbterm;
extern struct con_in_def con_in_ikbd;

struct con_out_def *conout = 0;
struct con_in_def *conin = 0;

void
con_init()
{
	/* conout = &con_out_mfp; */
	conout = &con_out_fbterm;
	conin = &con_in_ikbd;

	fb_init();

	if (conout != 0) {
		conout->init();
		msgbuf_print(conout);
	}

	if (conin != 0)
		conin->init();

	printf("console: ");
	if (conout != 0)
		printf("output %s ", conout->name);
	if (conin != 0)
		printf("intput %s ", conin->name);

	printf("\n");
}

void
con_putc(uint8_t c)
{
	/*
	 * Things are saved to a buffer that can be replayed after console
	 * init/change or using a command.
	 */
	msgbuf_putc(c);

	if (conout != 0)
		conout->putc(c);
}

uint8_t
con_getc()
{
	if (conin == 0)
		return 0;

	return conin->getc();
}

