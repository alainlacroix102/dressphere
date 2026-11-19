#include "common.h"

/* Provisional translation unit: real file boundaries not yet known. */
/* eecc-asflags: -G0 */

typedef struct {
    /* 0x00 */ u8 pad0[4];
    /* 0x04 */ s8 unk4;
    /* 0x05 */ u8 pad5[0x10 - 0x5];
    /* 0x10 */ s16 unk10;
    /* 0x12 */ u8 pad12[0x16 - 0x12];
    /* 0x16 */ s16 unk16;
} Unk5AC730;

typedef struct {
    /* 0x0 */ s16 x;
    /* 0x2 */ s16 y;
    /* 0x4 */ s16 z;
    /* 0x6 */ s16 w;
    /* 0x8 */ s16 h;
    /* 0xA */ s16 rot[3];
} UnkPlacement;

extern Unk5AC730 *D_005AC730[12];
extern f32 D_0046BBA0[];
extern s32 D_0046B690[];

extern void func_0033EE50(void *base, s32 n, s32 size, s32 (*cmp)(const void *, const void *)); /* qsort */
extern void func_00320798(void *dst, void *src, f32 *rot);
extern void func_00320458(void *dst, void *src, f32 *pos);
extern void func_002ECC38(s32);
extern void func_002ECD10(s32);
extern void func_002EBCC0(s32 reg, u64 val); /* GS register write? 0x47 = TEST_1 */
extern void func_002EC9C8(s32, s32, s32, s32, s32 *);
extern void func_002EA878(void);
extern void func_0031D4C8(s32, s32);

void func_002F2BA0(void) {
}

s32 func_002F2BC8(Unk5AC730 **a, Unk5AC730 **b);

void func_002F2BA8(void) {
    func_0033EE50(D_005AC730, 12, 4, (void *)func_002F2BC8);
}

s32 func_002F2BC8(Unk5AC730 **a, Unk5AC730 **b) {
    Unk5AC730 *pa = *a;
    Unk5AC730 *pb = *b;
    s32 x;
    s32 y;

    if (pa == NULL) {
        return pb != NULL ? -1 : 0;
    }
    if (pb == NULL) {
        return 1;
    }
    x = pa->unk4 + pa->unk16;
    y = pb->unk4 + pb->unk16;
    if (x < y) {
        return 1;
    }
    return y < x ? -1 : 0;
}

void func_002F2C20(Unk5AC730 *p, s16 v) {
    p->unk10 = v;
}

void func_002F2C28(void *mtx, UnkPlacement *a) {
    f32 pos[4];
    f32 rot[4];
    s32 i;

    /* angles are 4096 units per half turn; wrap into (-pi, pi] */
    for (i = 0; i < 3; i++) {
        rot[i] = a->rot[i] * 3.1415927f * 2.0f / 4096.0f;
        if (rot[i] > 3.1415927f) {
            rot[i] -= 6.2831855f;
        }
    }
    pos[0] = a->x + a->w / 2;
    pos[1] = a->y + a->h / 2;
    pos[2] = -64.0f;
    rot[3] = 0.0f;
    pos[3] = 0.0f;
    func_00320798(mtx, D_0046BBA0, rot);
    func_00320458(mtx, mtx, pos);
}

void func_002F2D58(s16 *p) {
    func_002ECC38(2);
    func_002ECD10(2);
    func_002EBCC0(0x47, 0x20002);
    func_002EC9C8(0, 0, p[2], p[3] * 0x455 / 1024, D_0046B690);
    func_002EA878();
    func_0031D4C8(0, 0);
    func_002EBCC0(0x47, 0x2001D);
    func_002EA878();
}

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
