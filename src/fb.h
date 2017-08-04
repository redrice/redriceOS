#include <stdint.h>

void fb_init();
void fb_putc(const char c, const uint16_t x, const uint16_t y);
void fb_bzero();

