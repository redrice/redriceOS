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
extern struct con_in_def con_in_mfp;
extern struct con_in_def con_in_ikbd;

struct con_out_def *conout = 0;
struct con_in_def *conin = 0;

void
con_init()
{
	struct con_out_def *tmpconout;
	struct con_in_def *tmpconin;


	tmpconout = &con_out_mfp;
	//tmpconout = &con_out_fbterm;
	tmpconin = &con_in_ikbd;
	//tmpconin = &con_in_mfp;

	fb_init();

	if (tmpconout != 0)
		tmpconout->init();

	if (tmpconin != 0)
		tmpconin->init();

	conout = tmpconout;
	conin = tmpconin;

	if (conout != 0)
		msgbuf_print(conout);

	printf("console: ");
	if (conout != 0)
		printf("output %s ", conout->name);
	if (conin != 0)
		printf("input %s ", conin->name);

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

