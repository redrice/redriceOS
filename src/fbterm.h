#ifndef _FBTERM_H_
#define _FBTERM_H_

#include <stdint.h>

#include "fb.h"

struct fbterm_dev {
	uint16_t curtx;
	uint16_t curty;

	uint16_t maxtx;
	uint16_t maxty;

	const struct shifter_mode_def *mode;
};

void fbterm_init();
void fbterm_putc(uint8_t);
void fbterm_blit_char(const uint8_t, const uint16_t, const uint16_t);

#endif /* _FBTERM_H_ */

