#include "fbterm.h"
#include "fb.h"

static struct fbterm_dev fbt;

void
fbterm_init()
{
	fbt.curx = 0;
	fbt.cury = 0;
}


/* TODO: Currently no checks for max x and max y; no scrolling etc */
void
fbterm_putc(uint8_t c)
{
//	const char *c = string;

//	while (*c != 0) {
		if (c != '\n') {
			fb_putc(c, fbt.curx++, fbt.cury);
		} else {
			fbt.curx = 0;
			fbt.cury++; 
		}
//		c++;
//	}
}

