#ifndef _IPL_H_
#define _IPL_H_

#include <stdint.h>

void ipl_get(__reg("a0") uint8_t *);
void ipl_set(__reg("a0") uint8_t *);

#endif /* _IPL_H_ */

