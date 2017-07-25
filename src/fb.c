#include "console_font.h"

// Shifter info

#define SHIFTER_PALETTE_SIZE 16
#define SHIFTER_FRAMEBUFFER_SIZE (640*400/8)

#define shifter_base (0xffff8200)
struct shifter_regs {
	char __padd0;
	char addr_hi;
	char __padd1;
	char addr_md;
	char __padd2;
	char counter_hi;
	char __padd3;
	char counter_md;
	char __padd4;
	char counter_lo;
	short sync;
	char __padd5;
	char addr_lo;
	char __padd6[2+3*16];
	unsigned short colors[SHIFTER_PALETTE_SIZE];
	unsigned char mode;
};
#define shifter (*(volatile struct shifter_regs *)(shifter_base))

enum SHIFTER_MODES {
	SHIFTER_MODE_320x200x4 = 0,
	SHIFTER_MODE_640x200x2,
	SHIFTER_MODE_640x400x1,
};

struct shifter_mode {
	unsigned int width;
	unsigned int height;
	unsigned int bit_planes;
	unsigned int stride;
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

static unsigned short framebuffer_palette[SHIFTER_PALETTE_SIZE] = {
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
	char *framebuffer;
};

static struct framebuffer_dev fb_dev = {
	.framebuffer = (char*)0x300000, // TODO: alloc?
};

void
fb_init()
{
	shifter.mode = SHIFTER_MODE_320x200x4;
	//shifter.mode = SHIFTER_MODE_640x400x1;

	/* TODO: allocate framebuffer */
	shifter.addr_hi = ((int)fb_dev.framebuffer >> 16);
	shifter.addr_md = ((int)fb_dev.framebuffer >> 8);

	for (int i = 0; i < SHIFTER_PALETTE_SIZE; i++) {
		shifter.colors[i] = framebuffer_palette[i];
	}
	
}

void
fb_putc(const char c, const int x, const int y)
{
	/* TODO: write a blitter */
	const unsigned char *glyph = font8x8_basic[c];
	const int font_height = 8;
	//int screen_width = 320/2; // bytes per line

	struct shifter_mode *current_mode = &shifter_modes[0];
	
	int bit_plane_width = 2;
	int offset = x >> 1; //  planes
	int byte_offset = x & 0x1; // mod 4

	int offset_x = (x >> 1) * current_mode->bit_planes * bit_plane_width;

	/* TODO: reduce the amount of calculations */
	for (int i = 0; i < font_height; i++) {
		unsigned char glyph_line = glyph[i];
		unsigned int index = (i + y * font_height) * current_mode->stride + offset_x + byte_offset;
		unsigned char mirrored_glyph_line = 0;

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
