#include <stdint.h>
#include <strings.h>

#include "hardware_atarist.h"
#include "console_font.h"

// Shifter info

#define SHIFTER_PALETTE_SIZE 16
#define SHIFTER_FRAMEBUFFER_SIZE (640*400/8)

struct shifter_regs {
	uint8_t __padd0;
	uint8_t addr_hi;
	uint8_t __padd1;
	uint8_t addr_md;
	uint8_t __padd2;
	uint8_t counter_hi;
	uint8_t __padd3;
	uint8_t counter_md;
	uint8_t __padd4;
	uint8_t counter_lo;
	int16_t sync;
	uint8_t __padd5;
	uint8_t addr_lo;
	uint8_t __padd6[2+3*16];
	uint16_t colors[SHIFTER_PALETTE_SIZE];
	uint8_t mode;
};
#define shifter (*(volatile struct shifter_regs *)(SHIFTER_BASE))

enum SHIFTER_MODES {
	SHIFTER_MODE_320x200x4 = 0,
	SHIFTER_MODE_640x200x2,
	SHIFTER_MODE_640x400x1,
};

struct shifter_mode {
	uint32_t width;
	uint32_t height;
	uint32_t bit_planes;
	uint32_t stride;
};

static struct shifter_mode shifter_modes[] = {
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


// Framebuffer info

static uint16_t framebuffer_palette[SHIFTER_PALETTE_SIZE] = {
	0x000, // black
	0x777, // white - only for debugging
	//0x400, // red
	0x040, // green
	0x420, // brown
	0x004, // blue
	0x404, // magenta
	0x044, // cyan
	0x444, // gray

	0x222, // dark gray
	0x722, // red
	0x272, // green
	0x772, // yellow
	0x227, // blue
	0x727, // magenta
	0x277, // cyan
	0x777, // white
};

struct framebuffer_dev {
	uint8_t *framebuffer;
};

struct framebuffer_dev fb_dev;

__section("fbram") uint8_t fbram[SHIFTER_FRAMEBUFFER_SIZE];

void
fb_init()
{
	fb_dev.framebuffer = fbram;

	shifter.mode = SHIFTER_MODE_640x400x1;

	shifter.addr_hi = ((int)fb_dev.framebuffer >> 16);
	shifter.addr_md = ((int)fb_dev.framebuffer >> 8);

	for (int i = 0; i < SHIFTER_PALETTE_SIZE; i++) {
		shifter.colors[i] = framebuffer_palette[i];
	}
	
}

void
fb_bzero()
{
	bzero(fb_dev.framebuffer, SHIFTER_FRAMEBUFFER_SIZE);
}

void
fb_putc(const uint8_t c, const uint16_t x, const uint16_t y)
{
	/* TODO: write a blitter */
	const uint8_t *glyph = font8x8_basic[c];
	const uint8_t font_height = 8;
	//int screen_width = 320/2; // bytes per line

	struct shifter_mode *current_mode = &shifter_modes[0];
	
//	int bit_plane_width = 2;
	int bit_plane_width = 1;
	int offset = x >> 1; //  planes
	int byte_offset = x & 0x1; // mod 4

	int offset_x = (x >> 1) * current_mode->bit_planes * bit_plane_width;

	/* TODO: reduce the amount of calculations */
	for (int i = 0; i < font_height; i++) {
		uint8_t glyph_line = glyph[i];
		uint32_t index = (i + y * font_height) * current_mode->stride + offset_x + byte_offset;
		uint8_t mirrored_glyph_line = 0;

		mirrored_glyph_line |= ((glyph_line & 1) << 7);
		mirrored_glyph_line |= ((glyph_line >> 1) & 1) << 6;
		mirrored_glyph_line |= ((glyph_line >> 2) & 1) << 5;
		mirrored_glyph_line |= ((glyph_line >> 3) & 1) << 4;
		mirrored_glyph_line |= ((glyph_line >> 4) & 1) << 3;
		mirrored_glyph_line |= ((glyph_line >> 5) & 1) << 2;
		mirrored_glyph_line |= ((glyph_line >> 6) & 1) << 1;
		mirrored_glyph_line |= ((glyph_line >> 7) & 1);

		fb_dev.framebuffer[index] = mirrored_glyph_line;
	}
}
