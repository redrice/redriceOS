#include "con.h"
#include "fb.h"
#include "fbterm.h"

struct con_dev {
	void (*putc)(uint8_t);
};

struct con_dev console;

void
con_init()
{
	fb_init();
	fbterm_init();	
	console.putc = &fbterm_putc;
}

void
con_putc(uint8_t c)
{
	console.putc(c);	
}

