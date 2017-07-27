#include "fb.h"
#include "console.h"

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
	struct console_dev con;
	char itoa_buffer[] = "   ";

	// initialize framebuffer and console
	fb_init();
	console_init(&con);

	console_print(&con, "redriceOS booting...\n");

	naive_itoa((int)framebuffer & 0xFF, itoa_buffer);
	console_print(&con, "framebuffer alignment: ");
	console_print(&con, itoa_buffer);

	while (1) {}
}

