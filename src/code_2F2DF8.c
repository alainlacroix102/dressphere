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

extern void func_0031D4C8(s32, s32);
extern void func_002ECC38(s32);
extern void func_002ECD10(s32);
extern void func_002EA878(void);

void func_002F2E48(u32 a) {
    u8 off;

    func_0031D4C8(0, 0);
    off = ~a & 1;
    func_002ECC38(off);
    func_002ECD10(off);
    func_002EA878();
    func_0031D4C8(0, 0);
}

extern s16 D_0046C4C8[4];

void func_002F2EA0(s32 *a, s32 *b, s32 *c, s32 *d) {
    if (a != NULL) {
        *a = D_0046C4C8[0];
    }
    if (b != NULL) {
        *b = D_0046C4C8[1];
    }
    if (c != NULL) {
        *c = D_0046C4C8[2];
    }
    if (d != NULL) {
        *d = D_0046C4C8[3];
    }
}

s16 *func_002F2EE8(void) {
    return D_0046C4C8;
}

typedef struct {
    /* 0x000 */ u8 pad0[0x140];
    /* 0x140 */ s32 unk140[1];
} Unk46B3F0;

extern Unk46B3F0 D_0046B3F0;
extern char D_00489400[];

extern s32 func_0033ED50(const char *fmt, ...); /* likely printf */
extern void func_001D1C78(s32, s32);
extern void func_001D0B68(s32);

void func_002F2EF8(s32 i) {
    func_0033ED50(D_00489400, D_0046B3F0.unk140[i]);
    func_001D1C78(i, D_0046B3F0.unk140[i]);
    func_001D0B68(i);
}
