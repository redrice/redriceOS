#include <stdio.h>
#include <stdint.h>
#include <strings.h>

#include "hardware_atarist.h"
#include "mfp.h"
#include "mmio.h"
#include "fb.h"

#define SHIFTER_FRAMEBUFFER_SIZE (640*400/8)

extern const uint8_t logo_data[];

static const struct shifter_mode_def shifter_modes[] = {
	[SHIFTER_MODE_320x200x4] = {
		.width = 320,
		.height = 200,
		.bit_planes = 4,
		.stride = 320 / 8 * 4
	},
	[SHIFTER_MODE_640x200x2] = {
		.width = 640,
		.height = 200,
		.bit_planes = 2,
		.stride = 640 / 8 * 2,
	},
	[SHIFTER_MODE_640x400x1] = {
		.width = 640,
		.height = 400,
		.bit_planes = 1,
		.stride = 640 / 8,
	}
};

const struct shifter_mode_def *current_mode;

__section("fbram") volatile uint8_t fbram[SHIFTER_FRAMEBUFFER_SIZE];

void
fb_register_write_1(uint8_t offset, uint8_t value) 
{
	mmio_write_1(SHIFTER_BASE + offset, value);
}

void
fb_init()
{
	if(mfp_register_read(MFP_GPDR) & MFP_GPIO_MMD)  {
		/* not really supported at the moment */
		fb_register_write_1(SHIFTER_MODE, SHIFTER_MODE_640x200x2);
		current_mode = &(shifter_modes[SHIFTER_MODE_640x200x2]);
	} else {
		fb_register_write_1(SHIFTER_MODE, SHIFTER_MODE_640x400x1);
		current_mode = &(shifter_modes[SHIFTER_MODE_640x400x1]);
	}

	fb_register_write_1(SHIFTER_ADDRESS_HI, ((uint8_t) ((uint32_t)fbram >> 16)));
	fb_register_write_1(SHIFTER_ADDRESS_MD, ((uint8_t) ((uint32_t)fbram >> 8)));

	fb_register_write_1(SHIFTER_PALETTE, 0x10);

	printf("fb: framebuffer mode %u x %u, %u bpl\n",
	    current_mode->width, current_mode->height,
	    current_mode->bit_planes);

	/* clear the screen */
        fb_bzero();

	/* draw the logo at upper right corner of the screen */
	fb_blit_sprite_1bpl(logo_data, (64*64)/8, 576, 0, 64, 64);
}

/*
 * Clear the screen by filling it with 0 bytes.
 */
void
fb_bzero()
{
	bzero(fbram, SHIFTER_FRAMEBUFFER_SIZE);
}

const struct shifter_mode_def *
fb_mode_get()
{
	return current_mode;
}

/*
 * Simplified blitting routine:
 * Blit 1-bitplane sprite onto 1-bitplane screen (fbram).
 *
 * src - pointer to memory holding the sprite data
 * len - size of sprite in bytes
 * x - horizontal position of upper left corner of sprite rectangle on screen
 * y - vertical position of upper left corener of sprite rectangle on screen
 * rx - width of sprite rectangle
 * ry - width of sprite rectangle
 *
 * Considering that this routine is copying whole bytes, it can only work on
 * sprites that have size value multiple of 8 pixels (e.g. 8x8, 8x16, 16x16...).
 * Destination values also have to be aligned to 8 pixels.
 */
void
fb_blit_sprite_1bpl(const uint8_t *src, const uint16_t len, const uint16_t x, const uint16_t y, const uint16_t rx, const uint16_t ry)
{
	uint16_t i, cur_rx, cur_ry;
	uint16_t off, off_x, off_y;

	i = 0; cur_rx = 0; cur_ry = 0;

	while (i < len) {

		if (cur_rx >= rx) {
			cur_rx = 0;
			cur_ry++;
		}

		/* there are 8 pixels in one byte */
		off_x = (x / 8) + (cur_rx / 8);
		off_y = (y + cur_ry) * current_mode->stride;
		off = off_y + off_x;

		/*printf("writing %p to %p\n", &src[i], &fbram[off]);*/
		fbram[off] = src[i];

		cur_rx+=8;
		i++;
	}
}

