#include <stdio.h>
#include <stdint.h>
#include <strings.h>

#include "hardware_atarist.h"
#include "mfp.h"
#include "mmio.h"
#include "fb.h"

#define SHIFTER_FRAMEBUFFER_SIZE (640*400/8)

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
	mmio_write_1(SHIFTER_BASE + offset, &value);
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

//	for (int i = 0; i < SHIFTER_PALETTE_SIZE; i++) {
//		shifter.colors[i] = framebuffer_palette[i];
//	}

	printf("fb: framebuffer mode %u x %u, %u bpl\n",
	    current_mode->width, current_mode->height,
	    current_mode->bit_planes);
}

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

void
fb_blit_sprite_1bpl(const uint8_t *charp, const uint16_t len, const uint16_t x, const uint16_t y, const uint16_t rx, const uint16_t ry)
{
	uint16_t i, cur_rx, cur_ry;
	uint16_t off, off_x, off_y;

	i = 0;

	cur_rx = 0;
	cur_ry = 0;

	while (i < len) {

		if (cur_rx >= rx) {
			cur_rx = 0;
			cur_ry++;
		}

		/* there are 8 pixels in one byte */
		off_x = (x / 8) + (cur_rx / 8);
		off_y = (y + cur_ry) * current_mode->stride;
		off = off_y + off_x;

		/*printf("writing %p to %p\n", &charp[i], &fbram[off]);*/
		fbram[off] = charp[i];

		cur_rx+=8;

		i++;
	}
}

