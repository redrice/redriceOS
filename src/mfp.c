#include <stdint.h>

#include "hardware_atarist.h"
#include "mmio.h"
#include "mfp.h"

const struct mfp_int_def mfp_int[] = {
	{ MFP_INTCTRL_B, BIT(0), "Centronics Busy" }, /* lowest priority */
	{ MFP_INTCTRL_B, BIT(1), "RS-232 DCD" },
	{ MFP_INTCTRL_B, BIT(2), "RS-232 CTS" },
	{ MFP_INTCTRL_B, BIT(3), "BLiTTER" },
	{ MFP_INTCTRL_B, BIT(4), "Timer D" },
	{ MFP_INTCTRL_B, BIT(5), "Timer C" },
	{ MFP_INTCTRL_B, BIT(6), "ACIA" },
	{ MFP_INTCTRL_B, BIT(7), "FDC" },
	{ MFP_INTCTRL_A, BIT(0), "Timer B" },
	{ MFP_INTCTRL_A, BIT(1), "RS-232 TXD Error" },
	{ MFP_INTCTRL_A, BIT(2), "RS-232 TXD Buffer Empty" },
	{ MFP_INTCTRL_A, BIT(3), "RS-232 RXD Error" },
	{ MFP_INTCTRL_A, BIT(4), "RS-232 RXD Buffer Full" },
	{ MFP_INTCTRL_A, BIT(5), "Timer A" },
	{ MFP_INTCTRL_A, BIT(6), "RS-232 RI" },
	{ MFP_INTCTRL_A, BIT(7), "Monitor detect" } /* highest priority */
};

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

void
mfp_register_set(uint8_t offset, uint8_t bits)
{
	mmio_set_1((volatile uint8_t *)(MFP_BASE + offset), bits);
}

void
mfp_register_unset(uint8_t offset, uint8_t bits)
{
	mmio_unset_1((volatile uint8_t *)(MFP_BASE + offset), bits);
}

void
mfp_vector_set()
{
	/* Configure 68k vectors 0x40 to 0x4F. */
	mfp_register_write(MFP_VR, MFP_ST_VECTOR | MFP_VR_S);
}

void
mfp_init()
{
	mfp_vector_set();
}

void
mfp_interrupt_enable(uint8_t intnum)
{
	mfp_register_set(MFP_IMR + mfp_int[intnum].ctrl, mfp_int[intnum].bit);
	mfp_register_set(MFP_IER + mfp_int[intnum].ctrl, mfp_int[intnum].bit);
}

void
mfp_interrupt_disable(uint8_t intnum)
{
	mfp_register_unset(MFP_IMR + mfp_int[intnum].ctrl, mfp_int[intnum].bit);
	mfp_register_unset(MFP_IER + mfp_int[intnum].ctrl, mfp_int[intnum].bit);
	mfp_register_unset(MFP_IPR + mfp_int[intnum].ctrl, mfp_int[intnum].bit);
	mfp_register_unset(MFP_ISR + mfp_int[intnum].ctrl, mfp_int[intnum].bit);
}

