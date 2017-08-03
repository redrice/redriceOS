#include <stdio.h>

#include "fb.h"
#include "fbterm.h"
#include "con.h"

uint32_t phystop;

#pragma align(256)
static char *framebuffer[320];
#pragma align()


// Note: only unsigned byte to ascii, no divisions
void 
naive_itoa(unsigned char val, char *buffer)
{
	unsigned char digit = 0;
	unsigned char divisors[] = {100, 10, 1};
	int div_index = 0;
	int should_print = 0;

	char *digit_out = buffer;

	do {
		digit = 0;
		unsigned char current_div = divisors[div_index];
		while (val >= current_div) {
			val -= current_div;
			digit++;
		}
		
		if (1 == current_div || digit > 0) {
			should_print = 1;
		}

		if (should_print) {
			*digit_out++ = '0' + digit;
		}
	} while (++div_index < sizeof(divisors)/sizeof(unsigned char));
}

#pragma dontwarn 121
void
main(void)
{
	con_init();

	printf("redriceOS booting...\n");
	printf("framebuffer alignment: %x\n", (int)framebuffer & 0xFF);

	while (1) {}
}

