#ifndef _CON_H_
#define _CON_H_

#include <stdint.h> 

struct con_dev_def {
	const char *name;
	void (*putc)(uint8_t);
	void (*init)(void);
};

void con_init();
void con_putc(uint8_t);

#endif /* _CON_H_ */

