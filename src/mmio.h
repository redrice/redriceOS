#ifndef _MMIO_H_
#define _MMIO_H_

#include <stdint.h>

void mmio_read_1(__reg("a0") volatile uint8_t *, __reg("a1") uint8_t *);
void mmio_write_1(__reg("a0") volatile uint8_t *, __reg("a1") uint8_t *);

#endif /* _IPL_H_ */


