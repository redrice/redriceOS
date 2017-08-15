#ifndef _IPL_H_
#define _IPL_H_

#include <stdint.h>

#define IPL_HBL 2
#define IPL_VBL 4
#define IPL_MFP 6

void ipl_get(__reg("a0") uint8_t *);
void ipl_set(__reg("a0") uint8_t *);

#endif /* _IPL_H_ */

