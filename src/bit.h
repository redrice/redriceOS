#ifndef _BIT_H_
#define _BIT_H_

#define MAX(_x, _y) ((_x > _y) ? _x : _y)
#define MIN(_x, _y) ((_x) < (_y) ? (_x) : (_y))

/* create a value with only bit _x set */
#define BIT(_x) (1UL << (_x))

/* extract bit from field _x, from value _y */
//#define BITV(_y,_x) ((_y & BIT(_x)) >> (_x)) /// XXX

/* get bits _x through _y, _x < _y */
#define BITS(_x,_y) ((BIT(MAX((_x), (_y)) + 1) - 1) ^ (BIT(MIN((_x), (_y))) - 1))

#endif /* _BIT_H_ */
