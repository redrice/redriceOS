#include <stdint.h>

struct console_dev {
	uint16_t curx;
	uint16_t cury;
};

void console_init(struct console_dev *dev);
void console_print(struct console_dev *dev, const char *string);
