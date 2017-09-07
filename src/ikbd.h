#ifndef _IKBD_H_
#define _IKBD_H_

#include <stdint.h>

#define IKBD_LSHIFT	0x2A
#define IKBD_RSHIFT	0x36

#define IKBD_ALT	0x38

#define IKBD_RELEASE	0x80

uint8_t ikbd_getc();
void ikbd_init();

#endif /* _IKBD_H_ */

