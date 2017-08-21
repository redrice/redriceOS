#ifndef _MSGBUF_H_
#define _MSGBUF_H_
#include "con.h"

void msgbuf_init();
void msgbuf_putc(uint8_t);
void msgbuf_print(struct con_dev_def *);

#endif /* _MSGBUG_H_ */

