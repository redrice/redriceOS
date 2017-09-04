#ifndef _MMIO_H_
#define _MMIO_H_

#include <stdint.h>

#include "bus.h"

__reg("d0") uint8_t mmio_read_1(__reg("a0") bus_addr);
void mmio_write_1(__reg("a0") bus_addr, __reg("d0") uint8_t);
void mmio_set_1(__reg("a0") bus_addr, __reg("d0") uint8_t);
void mmio_unset_1(__reg("a0") bus_addr, __reg("d0") uint8_t);

#endif /* _MMIO_H_ */


