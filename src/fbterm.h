#include <stdint.h>

struct fbterm_dev {
	uint16_t curx;
	uint16_t cury;
};

void fbterm_init();
void fbterm_putc(uint8_t);

