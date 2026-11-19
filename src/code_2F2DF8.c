#include "common.h"

/* Provisional translation unit: real file boundaries not yet known. */

extern char D_0046BAA0[]; /* printf-style format string */

extern s32 func_00320210(char *buf, const char *fmt, ...); /* likely sprintf */
extern void *func_002ECDE8(s32);
extern void func_002EE598(void *, s32, char *);

void func_002F2DF8(s32 a, s32 b) {
    char buf[64];

    func_00320210(buf, D_0046BAA0, a);
    func_002EE598(func_002ECDE8(2), b, buf);
}
