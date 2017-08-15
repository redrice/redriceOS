#ifndef _MFP_H_
#define _MFP_H_

#include "bitop.h"

#define MFP_GPDR	1
#define MFP_GPDR_CB		BIT(0)	/* Centronics busy */
#define MFP_GPDR_DCD		BIT(1)	/* RS-232 DCD */
#define MFP_GPDR_CTS		BIT(2)	/* RS-232 CTS */
#define MFP_GPDR_KB_IRQ		BIT(4)	/* IKBD interrupt */
#define MFP_GPDR_FDC_IRQ	BIT(5)	/* FDC interrupt */
#define MFP_GPDR_RI		BIT(6)	/* RS-232 RI */
#define MFP_GPDR_MMD		BIT(7)	/* Mono monitor detect */

uint8_t mfp_gpio_read(void);
uint8_t mfp_register_read(uint8_t offset);
void mfp_register_write(uint8_t offset, uint8_t v);

#endif /* _MFP_H_ */

