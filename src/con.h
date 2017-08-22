#ifndef _CON_H_
#define _CON_H_

#include <stdint.h> 

struct con_out_def {
	const char *name;
	void (*putc)(uint8_t);
	void (*init)(void);

	/* state */
};

struct con_in_def {
	const char *name;
	uint8_t (*getc)();
	void (*init)(void);

	/* void *state;	*/
};

void con_init();
void con_putc(uint8_t);
uint8_t con_getc();

#endif /* _CON_H_ */

