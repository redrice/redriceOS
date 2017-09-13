#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "msgbuf.h"
#include "con.h"

#define MSGBUF_SIZE 512 

static char *msgbuf;
static uint16_t msgbuf_pos = 0;

/* this whole function sucks and should be rewritten */
static void
msgbuf_cut()
{
	char *newmsgbuf;

	newmsgbuf = malloc(MSGBUF_SIZE);

	/* XXX debug */
	printf_nobuf("\nmsgbuf: copying %p size %x to %p\n", msgbuf, 
	    MSGBUF_SIZE / 2, newmsgbuf);

	/* XXX: hold interrupts for a moment? */
	bzero(newmsgbuf, MSGBUF_SIZE);
	memcpy(newmsgbuf, msgbuf + (MSGBUF_SIZE / 2), MSGBUF_SIZE / 2);	
	
	free(msgbuf);

	msgbuf = newmsgbuf;
	msgbuf_pos = (MSGBUF_SIZE / 2);
}

void
msgbuf_init()
{
	msgbuf = malloc(MSGBUF_SIZE);	
	bzero(msgbuf, MSGBUF_SIZE);
}

void
msgbuf_putc(uint8_t c)
{
	msgbuf[msgbuf_pos++] = c;

	if (msgbuf_pos > MSGBUF_SIZE)
		msgbuf_cut();
}	

void
msgbuf_print(struct con_out_def *console)
{
	char *printpos;

	printpos = msgbuf;

	while (*printpos != 0) {
		console->putc(*printpos++);
	}	
}

