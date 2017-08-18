#ifndef _ACIA_H_
#define _ACIA_H_

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "bus.h"
#include "bit.h"

#define ACIA_TXD	2
#define ACIA_RXD	2

#define ACIA_CR		0
#define ACIA_CR_DIV		BITS(1,0)	/* Counter divide select */
#define ACIA_CR_DIV_1			0
#define ACIA_CR_DIV_16			1
#define ACIA_CR_DIV_64			2
#define ACIA_CR_RESET			3
#define ACIA_CR_WORDSEL		BITS(4,2)	/* Word select */
#define ACIA_CR_WORDSEL_SHIFT	2
#define ACIA_CR_WORDSEL_7B_EP_2SB	0
#define ACIA_CR_WORDSEL_7B_OP_2SB	1
#define ACIA_CR_WORDSEL_7B_EP_1SB	2
#define ACIA_CR_WORDSEL_7B_OP_1SB	3
#define ACIA_CR_WORDSEL_8B_2SB		4
#define ACIA_CR_WORDSEL_8B_1SB		5
#define ACIA_CR_WORDSEL_8B_EP_1SB	6
#define ACIA_CR_WORDSEL_8B_OP_1SB	7
#define ACIA_CR_TC_TXDINT	BIT(5)		/* Transmit control, TXD int. */
#define ACIA_CR_TC_RTS		BIT(6)		/* Transmit control, RTS */
#define ACIA_CR_TC_BREAK	BIT(5)|BIT(6)	/* Send break */
#define ACIA_CR_RECVIRQ		BIT(7)		/* Receive interrupt enable */

#define ACIA_SR		0
#define ACIA_SR_RDRF		BIT(0)		/* Receive register full */
#define ACIA_SR_TDRE		BIT(1)		/* Transmit register empty */
#define ACIA_SR_DCD		BIT(2)		/* Data carrier detect */
#define ACIA_SR_CTS		BIT(3)		/* Clear to send */
#define ACIA_SR_FE		BIT(4)		/* Framing error */
#define ACIA_SR_OVRN		BIT(5)		/* Receiver overrun */
#define ACIA_SR_PE		BIT(6)		/* Parity error */
#define ACIA_SR_IRQ		BIT(7)		/* Interrup request */

struct acia_state {
	bus_addr base;	
};

void acia_control_write(struct acia_state *, uint8_t);
uint8_t acia_status_read(struct acia_state *);
uint8_t acia_data_read(struct acia_state *);
void acia_data_write(struct acia_state *, uint8_t);
void acia_configure(struct acia_state *, uint8_t);

#endif /* _ACIA_H_ */
