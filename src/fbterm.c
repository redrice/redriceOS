#include <stdio.h>

#include "fbterm.h"
#include "fb.h"
#include "con.h"
#include "vt220iso8x8.h"

static struct fbterm_dev fbt;

const struct con_out_def con_out_fbterm = {
	"fbterm", fbterm_putc, fbterm_init
};

static const uint8_t *font_data = vt220iso8x8_data;
static const uint8_t font_char_width = 8;	/* pixels */
static const uint8_t font_char_height = 8;	/* pixels */
static const uint8_t font_char_size = 8; /* bytes */// (font_char_width * font_char_height) / 8;

void
fbterm_init(void)
{
	fbt.curtx = 0;
	fbt.curty = 0;

	fbt.mode = fb_mode_get();	

	fbt.maxtx = fbt.mode->width / font_char_width;
	fbt.maxty = fbt.mode->height / font_char_height;

	fb_bzero();

	printf("fbterm: %u x %u characters terminal\n", fbt.maxtx, fbt.maxty);
}


/* TODO: Currently no checks for max x and max y; no scrolling etc */
void
fbterm_putc(uint8_t c)
{
//	const char *c = string;

//	while (*c != 0) {
		if (c != '\n') {
//			fb_putc(c, fbt.curtx++, fbt.curty);
			fbterm_blit_char(c, fbt.curtx++, fbt.curty);
		} else {
			fbt.curtx = 0;
			fbt.curty++; 
		}
//		c++;
//	}
}

void
fbterm_blit_char(const uint8_t c, const uint16_t tx, const uint16_t ty)
{
	const uint8_t *charp;
	uint16_t x, y;

	charp = font_data + (font_char_size * c);

	x = tx * font_char_width;
	y = ty * font_char_height;

	//printf("sw blit char at %p to x %d y %d\n", charp, x, y);

	fb_blit_sprite_1bpl(charp, font_char_size, x, y, font_char_width,
	    font_char_height);
}

