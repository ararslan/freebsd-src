#include <sys/cdefs.h>
#if 0
#if defined(LIBC_SCCS) && !defined(lint)
__RCSID("$NetBSD: infinity.c,v 1.2 1998/11/14 19:31:02 christos Exp $");
#endif /* LIBC_SCCS and not lint */
#endif
__FBSDID("$FreeBSD: src/lib/libc/sparc64/gen/infinity.c,v 1.7.36.1 2010/02/10 00:26:20 kensmith Exp $");

/* infinity.c */

#include <math.h>

/* bytes for +Infinity on a sparc */
const union __infinity_un __infinity = { { 0x7f, 0xf0, 0, 0, 0, 0, 0, 0 } };

/* bytes for NaN */
const union __nan_un __nan = { { 0xff, 0xc0, 0, 0 } };
