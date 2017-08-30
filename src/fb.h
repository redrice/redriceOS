#ifndef _FB_H_
#define _FB_H_

#include <stdint.h>

#define SHIFTER_ADDRESS_HI	0x1
#define SHIFTER_ADDRESS_MD	0x3

#define SHIFTER_PALLETTE	0x40

#define SHIFTER_MODE		0x60
#define SHIFTER_MODE_320x200x4		0
#define SHIFTER_MODE_640x200x2		1
#define SHIFTER_MODE_640x400x1		2

struct shifter_mode_def {
	uint32_t width;
	uint32_t height;
	uint32_t stride;
	uint8_t bit_planes;
};

void fb_init();
void fb_putc(const char, const uint16_t, const uint16_t);
void fb_bzero();
const struct shifter_mode_def * fb_mode_get();
void fb_blit_sprite_1bpl(const uint8_t *, const uint16_t, const uint16_t, const uint16_t, const uint16_t, const uint16_t);

#endif /* _FB_H_ */

