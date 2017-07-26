#include "console.h"
#include "fb.h"


void
console_init(struct console_dev *dev)
{
	dev->curx = 0;
	dev->cury = 0;
}


/* TODO: Currently no checks for max x and max y; no scrolling etc */
/* XXX: I think console_print needs to be independent of underlying terminal 
 * implementation, i.e. any changes to dev->cur... needs to happen in an
 * intermediate layer. */
void
console_print(struct console_dev *dev, const char *string)
{
	const char *c = string;

	while (*c != 0) {
		if (*c != '\n') {
			fb_putc(*c, dev->curx++, dev->cury);
		} else {
			dev->curx = 0;
			dev->cury++; 
		}
		c++;
	}
}
