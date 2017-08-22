#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

#include "acia.h"
#include "bus.h"
#include "mmio.h"

void
acia_control_write(struct acia_state *as, uint8_t value)
{
	 mmio_write_1((as->base + ACIA_CR), &value);
}

uint8_t
acia_status_read(struct acia_state *as)
{
	uint8_t value;

	mmio_read_1(as->base + ACIA_SR, &value);

	return value;
}

uint8_t
acia_data_read(struct acia_state *as)
{
	uint8_t value;

	mmio_read_1(as->base + ACIA_RXD, &value);

	return value;
}

void
acia_data_write(struct acia_state *as, uint8_t value)
{
	while (acia_status_read(as) ^ ACIA_SR_TDRE)
		;;

	mmio_write_1(as->base + ACIA_TXD, &value);
}

void
acia_configure(struct acia_state *as, uint8_t cr)
{
	acia_control_write(as, ACIA_CR_RESET);
	acia_control_write(as, cr);
}

