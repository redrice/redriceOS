#include "fbterm.h"
#include "fb.h"
#include "con.h"

static struct fbterm_dev fbt;

const struct con_dev_def con_dev_fbterm = {
	"Framebuffer console", fbterm_putc, fbterm_init
};

void
fbterm_init(void)
{
	fbt.curx = 0;
	fbt.cury = 0;

	fb_bzero();
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

