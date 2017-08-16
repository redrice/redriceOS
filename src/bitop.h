#ifndef _BITOP_H_
#define _BITOP_H_

#define MAX(a, b) ((a > b) ? a : b)
#define MIN(a, b) ((a) < (b) ? (a) : (b))

/* create a value with only bit x set */
#define BIT(x) (1UL << (x))

/* extract bit from field x, from value y */
#define BITV(y,x) ((y & BIT(x)) >> (x))

/* get bits x through y, x < y */
#define BITS(x,y) ((BIT(MAX((x), (y)) + 1) - 1) ^ (__BIT(MIN((x), (y))) - 1)) 

#endif /* _BITOP_H_ */
