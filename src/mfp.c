#include <stdint.h>

#include "hardware_atarist.h"
#include "mmio.h"
#include "mfp.h"

uint8_t
mfp_register_read(uint8_t offset)
{
	uint8_t value;

	mmio_read_1((volatile uint8_t *)(MFP_BASE + offset), &value);

	return value;
}

void
mfp_register_write(uint8_t offset, uint8_t value)
{
	mmio_write_1((volatile uint8_t *)(MFP_BASE + offset), &value);
}

