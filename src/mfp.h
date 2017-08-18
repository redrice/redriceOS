#ifndef _MFP_H_
#define _MFP_H_

#include <stdint.h>
#include <stdbool.h>
#include "bit.h"

#define MFP_REGS		24
/*
 * MFP registers, named according to the datasheet,
 * unless Atari specific, then it's my invention, lulz.
 */

#define MFP_GPDR	1	/* GPIO data register */
#define MFP_GPDR_GPIP0		BIT(0)
#define MFP_GPDR_GPIP1		BIT(1)
#define MFP_GPDR_GPIP2		BIT(2)
#define MFP_GPDR_GPIP3		BIT(3)
#define MFP_GPDR_GPIP4		BIT(4)
#define MFP_GPDR_GPIP5		BIT(5)
#define MFP_GPDR_GPIP6		BIT(6)
#define MFP_GPDR_GPIP7		BIT(7)
#define MFP_AER		3	/* Active edge register */
#define MFP_AER_GPIP0		BIT(0)
#define MFP_AER_GPIP1		BIT(1)
#define MFP_AER_GPIP2		BIT(2)
#define MFP_AER_GPIP3		BIT(3)
#define MFP_AER_GPIP4		BIT(4)
#define MFP_AER_GPIP5		BIT(5)
#define MFP_AER_GPIP6		BIT(6)
#define MFP_AER_GPIP7		BIT(7)
#define MFP_DDR		5	/* Data direction register */
#define MFP_DDR_GPIP0		BIT(0)
#define MFP_DDR_GPIP1		BIT(1)
#define MFP_DDR_GPIP2		BIT(2)
#define MFP_DDR_GPIP3		BIT(3)
#define MFP_DDR_GPIP4		BIT(4)
#define MFP_DDR_GPIP5		BIT(5)
#define MFP_DDR_GPIP6		BIT(6)
#define MFP_DDR_GPIP7		BIT(7)
#define MFP_IER		7
#define MFP_IERA	7	/* Interrupt enable register A */
#define MFP_IERA_TIMERB		BIT(0)
#define MFP_IERA_XMIT_ERROR	BIT(1)
#define MFP_IERA_XMIT_BUFEMPTY	BIT(2)
#define MFP_IERA_RCV_ERROR	BIT(3)
#define MFP_IERA_RCV_BUFFULL	BIT(4)
#define MFP_IERA_TIMERA		BIT(5)
#define MFP_IERA_GPIP6		BIT(6)
#define MFP_IERA_GPIP7		BIT(7)
#define MFP_IERB	9	/* Interrupt enable register B */
#define MFP_IERB_GPIP0		BIT(0)
#define MFP_IERB_GPIP1		BIT(1)
#define MFP_IERB_GPIP2		BIT(2)
#define MFP_IERB_GPIP3		BIT(3)
#define MFP_IERB_TIMERD		BIT(4)
#define MFP_IERB_TIMERC		BIT(5)
#define MFP_IERB_GPIP6		BIT(6)
#define MFP_IERB_GPIP5		BIT(7)
#define MFP_IPR		0xB
#define MFP_IPRA	0xB	/* Interrupt pending register A */
#define MFP_IPRA_TIMERB		BIT(0)
#define MFP_IPRA_XMIT_ERROR	BIT(1)
#define MFP_IPRA_XMIT_BUFEMPTY	BIT(2)
#define MFP_IPRA_RCV_ERROR	BIT(3)
#define MFP_IPRA_RCV_BUFFULL	BIT(4)
#define MFP_IPRA_TIMERA		BIT(5)
#define MFP_IPRA_GPIP6		BIT(6)
#define MFP_IPRA_GPIP7		BIT(7)
#define MFP_IPRB	0xD	/* Interrupt pending register B */
#define MFP_IPRB_GPIP0		BIT(0)
#define MFP_IPRB_GPIP1		BIT(1)
#define MFP_IPRB_GPIP2		BIT(2)
#define MFP_IPRB_GPIP3		BIT(3)
#define MFP_IPRB_TIMERD		BIT(4)
#define MFP_IPRB_TIMERC		BIT(5)
#define MFP_IPRB_GPIP6		BIT(6)
#define MFP_IPRB_GPIP5		BIT(7)
#define MFP_ISR		0xF
#define MFP_ISRA	0xF	/* Interrupt in-service register A */
#define MFP_ISRA_TIMERB		BIT(0)
#define MFP_ISRA_XMIT_ERROR	BIT(1)
#define MFP_ISRA_XMIT_BUFEMPTY	BIT(2)
#define MFP_ISRA_RCV_ERROR	BIT(3)
#define MFP_ISRA_RCV_BUFFULL	BIT(4)
#define MFP_ISRA_TIMERA		BIT(5)
#define MFP_ISRA_GPIP6		BIT(6)
#define MFP_ISRA_GPIP7		BIT(7)
#define MFP_ISRB	0x11	/* Interrupt in-service register B */
#define MFP_ISRB_GPIP0		BIT(0)
#define MFP_ISRB_GPIP1		BIT(1)
#define MFP_ISRB_GPIP2		BIT(2)
#define MFP_ISRB_GPIP3		BIT(3)
#define MFP_ISRB_TIMERD		BIT(4)
#define MFP_ISRB_TIMERC		BIT(5)
#define MFP_ISRB_GPIP6		BIT(6)
#define MFP_ISRB_GPIP5		BIT(7)
#define MFP_IMR		0x13
#define MFP_IMRA	0x13	/* Interrupt mask register A */
#define MFP_IMRA_TIMERB		BIT(0)
#define MFP_IMRA_XMIT_ERROR	BIT(1)
#define MFP_IMRA_XMIT_BUFEMPTY	BIT(2)
#define MFP_IMRA_RCV_ERROR	BIT(3)
#define MFP_IMRA_RCV_BUFFULL	BIT(4)
#define MFP_IMRA_TIMERA		BIT(5)
#define MFP_IMRA_GPIP6		BIT(6)
#define MFP_IMRA_GPIP7		BIT(7)
#define MFP_IMRB	0x15	/* Interrupt mask register B */
#define MFP_IMRB_GPIP0		BIT(0)
#define MFP_IMRB_GPIP1		BIT(1)
#define MFP_IMRB_GPIP2		BIT(2)
#define MFP_IMRB_GPIP3		BIT(3)
#define MFP_IMRB_TIMERD		BIT(4)
#define MFP_IMRB_TIMERC		BIT(5)
#define MFP_IMRB_GPIP6		BIT(6)
#define MFP_IMRB_GPIP5		BIT(7)
#define MFP_VR		0x17	/* Vector register */
#define MFP_VR_VNUM		BITS(7,4)
#define MFP_VR_S		BIT(3)	/* In-service register enable */
#define MFP_TCR_STOPPED			0x0
#define MFP_TCR_DELAY_P4		0x1
#define MFP_TCR_DELAY_P10		0x2
#define MFP_TCR_DELAY_P16		0x3
#define MFP_TCR_DELAY_P50		0x4
#define MFP_TCR_DELAY_P64		0x5
#define MFP_TCR_DELAY_P100		0x6
#define MFP_TCR_DELAY_P200		0x7
#define MFP_TCR_EVCNT			0x8
#define MFP_TCR_PWM_P4			0x9
#define MFP_TCR_PWM_P10			0xA
#define MFP_TCR_PWM_P16			0xB
#define MFP_TCR_PWM_P50			0xC
#define MFP_TCR_PWM_P64			0xD
#define MFP_TCR_PWM_P100		0xE
#define MFP_TCR_PWM_P200		0xF
#define MFP_TACR	0x19	/* Timer A control register */
#define MFP_TACR_AC		BITS(3,0)
#define MFP_TACR_RST_TAO	BIT(4)
#define MFP_TBCR	0x1B	/* Timer B control register */
#define MFP_TBCR_BC		BITS(3,0)
#define MFP_TBCR_RST_TAO	BIT(4)
#define MFP_TCDCR	0x1D	/* Timer C, D control regsiter */
#define MFP_TCDCR_DC		BITS(2,0)
#define MFP_TCDCR_CC		BITS(6,4)
#define MFP_TADR	0x1F	/* Timer A data register */
#define MFP_TBDR	0x21	/* Timer B data register */
#define MFP_TCDR	0x23	/* Timer C data register */
#define MFP_TDDR	0x25	/* Timer D data register */
#define MFP_SCR		0x27	/* Synchronous character register */
#define MFP_UCR		0x29	/* USART control register */
#define MFP_UCR_EO		BIT(1)	/* Even/odd parity */
#define MFP_UCR_PE		BIT(2)	/* Parity enable */
#define MFP_UCR_ST		BITS(4,3) /* Format and start/stop bits */
#define MFP_UCR_ST_SYNC			0	/* XXX: unset bits in above */
#define MFP_UCR_ST_ASYNC_S1T1		0x8	/* Async, start 1, stop 1 */
#define MFP_UCR_ST_ASYNC_S1T05		0x9	/* Async, start 1, stop 0.5 */
#define MFP_UCR_ST_ASYNC_S1T2		0x18	/* ASync, start 1, stop 2 */
#define MFP_UCR_CL		BITS(6,5) /* Character length */
#define MFP_UCR_CL_8BIT			0	/* XXX: unset bits in above */
#define MFP_UCR_CL_7BIT			0x20
#define MFP_UCR_CL_6BIT			0x40
#define MFP_UCR_CL_5BIT			0x60
#define MFP_UCR_CLK		BIT(7)	/* Data clocked at 1/16 of clock */
#define MFP_RSR		0x2B	/* Receiver status register */
#define MFP_RSR_RE		BIT(0)	/* Receiver enabled */
#define MFP_RSR_SS		BIT(1)	/* Synchronous strip */
#define MFP_RSR_MCIP		BIT(2)	/* Match/character in progress */
#define MFP_RSR_FSB		BIT(3)	/* Found/search of break */
#define MFP_RSR_FE		BIT(4)	/* Frame error */
#define MFP_RSR_PE		BIT(5)	/* Parity error */
#define MFP_RSR_OE		BIT(6)	/* Overrun error */
#define MFP_RSR_BF		BIT(7)	/* Buffer full */
#define MFP_TSR		0x2D	/* Transmitter status register */
#define MFP_TSR_TE		BIT(0)	/* Transmitter enable */
#define MFP_TSR_H		BIT(1)
#define MFP_TSR_L		BIT(2)
#define MFP_TSR_B		BIT(3)	/* Break */
#define MFP_TSR_END		BIT(4)
#define MFP_TSR_AT		BIT(5)	/* Auto-turnaround */
#define MFP_TSR_UE		BIT(6)	/* Underrun error */
#define MFP_TSR_BE		BIT(7)	/* Buffer empty */
#define MFP_UDR		0x2F	/* USART data register */

#define MFP_GPIO_CB		MFP_GPDR_GPIP0	/* Centronics busy */
#define MFP_GPIO_DCD		MFP_GPDR_GPIP1	/* RS-232 DCD */
#define MFP_GPIO_CTS		MFP_GPDR_GPIP2	/* RS-232 CTS */
#define MFP_GPIO_KB_IRQ		MFP_GPDR_GPIP4	/* IKBD interrupt */
#define MFP_GPIO_FDC_IRQ	MFP_GPDR_GPIP5	/* FDC interrupt */
#define MFP_GPIO_RI		MFP_GPDR_GPIP6	/* RS-232 RI */
#define MFP_GPIO_MMD		MFP_GPDR_GPIP7	/* Mono monitor detect */

#define MFP_ST_VECTOR		0x40	/* *4 = offset 0x100 */

#define MFP_INTS		16

#define MFP_TIMERA		0
#define MFP_TIMERB		1
#define MFP_TIMERC		2
#define MFP_TIMERD		3

#define MFP_INTCTRL_A		0
#define MFP_INTCTRL_B		2

#define MFP_ST_INT_CB		0
#define MFP_ST_INT_DCD		1
#define MFP_ST_INT_CTS		2
#define MFP_ST_INT_BLITTER	3
#define MFP_ST_INT_TIMERD	4	/* used for baud generation */
#define MFP_ST_INT_TIMERC	5
#define MFP_ST_INT_ACIA		6
#define MFP_ST_INT_FDC		7
#define MFP_ST_INT_TIMERB	8
#define MFP_ST_INT_XMIT_ERROR	9
#define MFP_ST_INT_XMIT_BUFEMPTY 10
#define MFP_ST_INT_RCV_ERROR	11
#define MFP_ST_INT_RCV_BUFFULL	12
#define MFP_ST_INT_TIMERA	13
#define MFP_ST_INT_RI		14
#define MFP_ST_INT_MMD		15

struct mfp_int_def {
	const uint8_t ctrl;	/* interrupt controler A (0) or B (2) */
	const uint8_t bit;	/* bit controlling given interrupt */
	const char *desc;
};

struct mfp_timer_def {
	const uint8_t tcroff;	/* control register offset */
	const uint8_t tcrshift;	/* control register shift left */
	const uint8_t tcrbits;	/* control register bits for a given timer */
	const uint8_t tdroff;	/* data register offset */
	const uint8_t intnum;	/* interrupt number */
	const bool delayonly;	/* has only delay modes of operation */
	const char *name;
};

uint8_t mfp_register_read(uint8_t);
void mfp_register_write(uint8_t, uint8_t);
void mfp_register_set(uint8_t, uint8_t);
void mfp_register_unset(uint8_t, uint8_t);
void mfp_vector_set();
void mfp_init();
void mfp_interrupt_enable(uint8_t);
void mfp_interrupt_disable(uint8_t);
void mfp_interrupt_stat_print();
void mfp_interrupt_stat_increment(uint8_t);
void mfp_timer_setup(uint8_t, uint8_t, uint8_t);
void mfp_timer_stop(uint8_t);
void mfp_timer_handler_set(uint8_t, void(*)(void));

#endif /* _MFP_H_ */

