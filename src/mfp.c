#include <stdint.h>
#include <stdio.h>

#include "hardware_atarist.h"
#include "exception.h"
#include "mmio.h"
#include "mfp.h"

const struct mfp_int_def mfp_int[] = {
	{ MFP_INTCTRL_B, BIT(0), "Centronics Busy" }, /* lowest priority */
	{ MFP_INTCTRL_B, BIT(1), "RS-232 DCD" },
	{ MFP_INTCTRL_B, BIT(2), "RS-232 CTS" },
	{ MFP_INTCTRL_B, BIT(3), "BLiTTER" },
	{ MFP_INTCTRL_B, BIT(4), "Timer D" },
	{ MFP_INTCTRL_B, BIT(5), "Timer C" },
	{ MFP_INTCTRL_B, BIT(6), "Keyboard/MIDI ACIA" },
	{ MFP_INTCTRL_B, BIT(7), "FDC/HDD" },
	{ MFP_INTCTRL_A, BIT(0), "Timer B" },
	{ MFP_INTCTRL_A, BIT(1), "RS-232 TXD Error" },
	{ MFP_INTCTRL_A, BIT(2), "RS-232 TXD Buffer Empty" },
	{ MFP_INTCTRL_A, BIT(3), "RS-232 RXD Error" },
	{ MFP_INTCTRL_A, BIT(4), "RS-232 RXD Buffer Full" },
	{ MFP_INTCTRL_A, BIT(5), "Timer A" },
	{ MFP_INTCTRL_A, BIT(6), "RS-232 RI" },
	{ MFP_INTCTRL_A, BIT(7), "Monitor detect" } /* highest priority */
};

const struct mfp_timer_def mfp_timer[] = {
	{ MFP_TACR, 0, MFP_TACR_AC, MFP_TADR, MFP_ST_INT_TIMERA, false,
	    "Timer A" },
	{ MFP_TBCR, 0, MFP_TBCR_BC, MFP_TBDR, MFP_ST_INT_TIMERB, false,
	    "Timer B" },
	{ MFP_TCDCR, 4, MFP_TCDCR_CC, MFP_TCDR, MFP_ST_INT_TIMERC, true,
	    "Timer C" },
	{ MFP_TCDCR, 0, MFP_TCDCR_DC, MFP_TCDR, MFP_ST_INT_TIMERD, true,
	    "Timer D" }
};

const uint8_t mfp_timer_delay_divs[] =
	{ 0, 4, 10, 16, 50, 64, 100, 200 };

/*
 * Holds current state of timers.
 */
static struct mfp_timer_state_def mfp_timer_state[] = {
	{ false, 0, 0 },
	{ false, 0, 0 },
	{ false, 0, 0 },
	{ false, 0, 0 }
};

/*
 * Holds interrupt statistics (how many times a given MFP interrupt was fired).
 */
static uint32_t mfp_int_stats[MFP_INTS];

uint8_t
mfp_register_read(uint8_t offset)
{
	uint8_t value;

	mmio_read_1((MFP_BASE + offset), &value);

	return value;
}

void
mfp_register_write(uint8_t offset, uint8_t value)
{
	mmio_write_1(MFP_BASE + offset, &value);
}

void
mfp_register_set(uint8_t offset, uint8_t bits)
{
	mmio_set_1((MFP_BASE + offset), bits);
}

void
mfp_register_unset(uint8_t offset, uint8_t bits)
{
	mmio_unset_1((MFP_BASE + offset), bits);
}

/*
 * Set 68000 vector for MFP interrupts.
 */
void
mfp_vector_set()
{
	/* Configure 68k vectors 0x40 to 0x4F. */
//	mfp_register_write(MFP_VR, MFP_ST_VECTOR | MFP_VR_S);  // XXX
	mfp_register_write(MFP_VR, MFP_ST_VECTOR);
}

/*
 * Do the basic init of MFP.
 */
void
mfp_init()
{
	uint8_t i = 1;
	while(i < MFP_REGS) {
		mfp_register_write(i, 0);
		i++; i++;
	}

	mfp_vector_set();
}

/*
 * Enable a specific interrupt in MFP. Only gets serviced if IPL is 5 or lower.
 */
void
mfp_interrupt_enable(uint8_t intnum)
{
	mfp_register_set(MFP_IMR + mfp_int[intnum].ctrl, mfp_int[intnum].bit);
	mfp_register_set(MFP_IER + mfp_int[intnum].ctrl, mfp_int[intnum].bit);
}

/*
 * Disable an interrupt in MFP.
 */
void
mfp_interrupt_disable(uint8_t intnum)
{
	mfp_register_unset(MFP_IMR + mfp_int[intnum].ctrl, mfp_int[intnum].bit);
	mfp_register_unset(MFP_IER + mfp_int[intnum].ctrl, mfp_int[intnum].bit);
	mfp_register_unset(MFP_IPR + mfp_int[intnum].ctrl, mfp_int[intnum].bit);
	mfp_register_unset(MFP_ISR + mfp_int[intnum].ctrl, mfp_int[intnum].bit);
}

/*
 * Incrememnt a counter (counting how many times a given MFP interrupt was
 * fired). Should somehow be called automatically when MFP interrupt is
 * serviced. Currently needs to be called manually.
 */
void
mfp_interrupt_stat_increment(uint8_t intnum)
{
	(mfp_int_stats[intnum])++;	
}

/*
 * Print timer statistics, only valid if timer ISR updates mfp_int_stats[].
 */
void
mfp_interrupt_stat_print()
{
	uint8_t i;
	printf("MFP int stats: ");
	for(i = 0; i < MFP_INTS; i++)
		printf("%x ", mfp_int_stats[i]);

	printf("\n");
}

/*
 * Configure a timer according to provided parameters.
 */
void
mfp_timer_setup(uint8_t timerid, uint8_t mode, uint8_t data)
{
	uint8_t ctrl;

	if ((mode > 0x7) && (mfp_timer[timerid].delayonly)) {
		printf("%s does not support requested mode!\n",
		    mfp_timer[timerid].name);
		return;
	}

	ctrl = mfp_register_read(mfp_timer[timerid].tcroff);

	ctrl |= (mode << mfp_timer[timerid].tcrshift) &
	    mfp_timer[timerid].tcrbits;

	mfp_timer_state[timerid].tcr = mode;
	mfp_timer_state[timerid].otdr = data;
	mfp_timer_state[timerid].running = true;

	mfp_register_write(mfp_timer[timerid].tdroff, data);
	mfp_register_write(mfp_timer[timerid].tcroff, ctrl);
}

/*
 * Stop the timer, does not disable interrupt.
 */
void
mfp_timer_stop(uint8_t timerid)
{
	mfp_register_unset(mfp_timer[timerid].tcroff,
	    mfp_timer[timerid].tcrbits);

	mfp_timer_state[timerid].tcr = 0;
	mfp_timer_state[timerid].otdr = 0;
	mfp_timer_state[timerid].running = false;
}

/*
 * Set the handler to be executed once interrupt for a given timer fires.
 */
void
mfp_timer_handler_set(uint8_t timerid, void(*handler)(void))
{
	exception_handler_install(exception_vec_to_off(MFP_ST_VECTOR +
	    mfp_timer[timerid].intnum), handler);
}

/*
 * Get the timer frequency in Hz, this only works for timers configured in
 * delay mode.
 */
static uint32_t
mfp_timer_frequency(uint8_t timerid)
{
	uint32_t f;

	f = MFP_ST_CLK / mfp_timer_delay_divs[mfp_timer_state[timerid].tcr] /
	    mfp_timer_state[timerid].otdr;	

	return f;
}

/*
 * Print timer statistics.
 */
void
mfp_timer_stats_print()
{
	uint8_t tcr, i;

	printf("Timer\tMode\tHandler\tHz\n");

	for (i = 0; i < 4; i++) {
		printf("%s\t", mfp_timer[i].name);
		if (mfp_timer_state[i].running == false) {
			printf("Stopped\n");
			continue;
		}

		tcr = mfp_timer_state[i].tcr;

		if ((tcr > 0) && (tcr < 8))
			printf("Delay /%u\t", mfp_timer_delay_divs[tcr]);
		else if (tcr == 8)
			printf("Event counter\t");
		else if ((tcr > 8) && (tcr <= 15))
			printf("PWM /%u\t", mfp_timer_delay_divs[tcr-8]);
		else
			printf("?\t");

		printf("%p\t", exception_handler_get(
		    exception_vec_to_off(MFP_ST_VECTOR + mfp_timer[i].intnum))); 

		printf("%u\t", mfp_timer_frequency(i));

		printf("\n");
	}
}

void
mfp_serial_write(uint8_t c)
{
	while(!(mfp_register_read(MFP_TSR) & MFP_TSR_BE))
		;;	// XXX: bail out after some time with err

	mfp_register_write(MFP_UDR, c);
}

/* XXX needs to be customizable */
void
mfp_serial_init()
{
	mfp_register_write(MFP_UCR, MFP_UCR_ST_ASYNC_S1T1 | MFP_UCR_CLK);

	mfp_timer_setup(MFP_TIMERD, MFP_TCR_DELAY_P4, 1);

	mfp_register_set(MFP_TSR, MFP_TSR_TE);
}

