#ifndef _EXCEPTION_H_
#define _EXCEPTION_H_

void exception_init(void);
void exception_handler_install(uint16_t, void(*)(void));
void exception_handler_unhandled(void);

#endif /* _EXCEPTION_H_ */

