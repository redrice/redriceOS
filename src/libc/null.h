#ifndef _NULL_H_
#define _NULL_H_

#ifdef __STDC__
typedef void *pointer;
#ifndef NULL
#define NULL (void *)0
#endif
#else /* not __STDC__ */
typedef char *pointer;
#ifndef NULL
#define NULL 0
#endif
#endif /*  not __STDC__ */

#endif /* _NULL_H_ */

