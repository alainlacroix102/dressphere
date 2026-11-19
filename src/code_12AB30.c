#include "common.h"

/* Provisional translation unit: real file boundaries not yet known. */

typedef struct {
    /* 0x00 */ s32 unk0[3];
    /* 0x0C */ s32 unkC;
} Unk3596B0; /* size = 0x10 */

/* Object passed to most functions here; layout only partially known. */
typedef struct {
    /* 0x000 */ u8 pad0[0x198];
    /* 0x198 */ s8 unk198;
    /* 0x199 */ u8 pad199;
    /* 0x19A */ s8 unk19A;
    /* 0x19B */ u8 pad19B[0x1B0 - 0x19B];
    /* 0x1B0 */ s64 unk1B0;
    /* 0x1B8 */ u8 pad1B8[0x77E - 0x1B8];
    /* 0x77E */ s16 unk77E;
} UnkObj;

extern Unk3596B0 *D_003596B0;
extern s32 D_0049B460[];
extern s32 D_0035473C;
extern s16 *D_0049B4B4;
extern s16 *D_0049B4B8;
extern s16 *D_0049B4BC;
extern s16 *D_0049B4C0;
extern f32 D_0049B4C4;
extern f32 D_0049B4D0;
extern s32 D_0049B4D4;
extern f32 D_003544A4;
extern f32 D_0049B4C8;
extern f32 D_003596D0;

#define ABS(x) ((x) < 0 ? -(x) : (x))

extern void func_00117160(void *, f32);
extern void func_001176E8(void *, f32);
extern void func_00117838(void *, f32);
extern void func_003202A0(f32 *, f32 *);
extern double atan2(double, double);
extern void func_0011BD10(void *, s32);
extern s32 func_00107508(void *, s32, s32);
extern s32 func_001079E0(void *, s32, s32, s32, s32, s32);
extern f32 func_0011D748(s32);
extern UnkObj *func_0011D300(void);
f32 func_0012AC70(void *, s16 *, s16 *);
void func_0012AE50(void *);
s32 func_0012AE98(UnkObj *, f32);

s32 func_0012AB30(s32 i) {
    s32 v = D_003596B0[i].unkC & 0x7F;

    if ((u32)(v - 0x30) < 0x10) {
        return D_0049B460[v - 0x30];
    }
    return v;
}

s32 func_0012AB78(UnkObj *p, s32 i) {
    u32 type = D_003596B0[i].unkC & 0x7F;
    s32 ret;

loop:
    switch (type) {
        case 1:
            return 1;
        case 2:
            ret = 1;
            if (p == func_0011D300()) {
                ret = 0;
            }
            return ret;
        case 14:
            return p == func_0011D300();
        case 13:
            return (s32)(p->unk1B0 >> 2) & 1;
        case 0x30 ... 0x3F:
            type = D_0049B460[type - 0x30];
            goto loop;
    }
    return 0;
}

f32 func_0012AC70(void *p, s16 *from, s16 *to) {
    f32 pad[8];
    f32 v[4];
    f32 ang;

    v[2] = to[0] - from[0];
    v[1] = 0.0f;
    v[0] = to[2] - from[2];
    func_003202A0(v, v);
    ang = atan2(v[0], v[2]) + 1.570796f;
    while (ang > 3.141592026f) {
        ang -= 6.283184052f;
    }
    while (ang < -3.141592026f) {
        ang += 6.283184052f;
    }
    func_00117838(p, ang);
    return ang;
}

void func_0012AD98(UnkObj *p) {
    func_0012AC70(p, D_0049B4B4, D_0049B4B8);
    func_00117160(p, func_0011D748(2));
    func_0011BD10(p, 1);
}

s32 func_0012ADE8(UnkObj *p) {
    s32 r = 0;

    if (D_0035473C & 0x40) {
        r = p->unk198 != 1;
    }
    return r;
}

void func_0012AE10(void *p, f32 a) {
    func_00117838(p, a);
    func_00117160(p, func_0011D748(2));
    func_0011BD10(p, 1);
}

void func_0012AE50(void *p) {
    func_001176E8(p, func_0012AC70(p, D_0049B4BC, D_0049B4C0));
    func_0011BD10(p, 4);
}

s32 func_0012AE98(UnkObj *p, f32 unused) {
    s8 tbl[18] = { 0, 0, 0, 0, 0, 1, 4, 5, 6, 7, 7, 8, 9, 9, 10, 10, 11, 12 };
    s32 idx = 23.0f - D_0049B4C4;
    s32 ret;

    func_001176E8(p, func_0012AC70(p, D_0049B4BC, D_0049B4C0));
    func_0011BD10(p, 3);
    ret = func_001079E0(p, func_00107508(p, 0, 0x25), 0, 1, tbl[idx], -1);
    p->unk77E = 1;
    return ret;
}

s32 func_0012AF78(UnkObj *p, s32 i) {
    s32 is15 = func_0012AB30(i) == 0xF;
    s32 flag = D_0035473C & 0x40;

    if (!is15) {
        return 0;
    }
    if (p->unk198 == 1) {
        return 0;
    }
    if (flag && ((s32)(p->unk1B0 >> 14) & 1)) {
        func_0012AD98(p);
        return 0;
    }
    func_0011BD10(p, 2);
    return 1;
}

#ifdef NON_MATCHING
/* Only difference: retail calls func_0012AD98 with jal + branch to the shared
 * epilogue; our compiler turns it into a tail call. */
void func_0012B000(UnkObj *p) {
    s32 flag = D_0035473C & 0x40;

    if ((s32)(p->unk1B0 >> 14) & 1) {
        if (p->unk198 != 1) {
            if (flag) {
                func_0012AD98(p);
            } else {
                func_0011BD10(p, 1);
                p->unk19A = 1;
            }
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/code_12AB30", func_0012B000);
#endif

#ifdef NON_MATCHING
/* Functionally equivalent; block layout differs (retail shares the first
 * `return 1` site, ours the last). */
s32 func_0012B080(UnkObj *p) {
    s32 flag;

    D_0049B4D4 = 0;
    flag = D_0035473C & 0x40;
    if (p->unk198 == 4) {
        if (D_0049B4D0 > 20.0f) {
            return 1;
        }
        D_0049B4D4 = 7;
        D_0049B4C4 = D_0049B4D0;
        D_003544A4 = D_0049B4D0;
        return 2;
    } else if (p->unk198 == 1) {
        if (D_0049B4D0 > 19.0f) {
            return 1;
        }
        if (D_0049B4D0 > 6.0f) {
            D_0049B4D4 = 6;
        }
        D_003544A4 = D_0049B4D0;
    } else {
        if (D_0049B4D0 > 22.0f) {
            if (!flag) {
                return 1;
            }
            D_0049B4D4 = 3;
            D_0049B4C4 = D_0049B4D0;
            return 3;
        }
        if (D_0049B4D0 > 6.0f) {
            if (!flag) {
                return 1;
            }
            D_0049B4D4 = 5;
            D_0049B4C4 = D_0049B4D0;
            D_003544A4 = D_0049B4D0;
            return 2;
        }
        if (D_003544A4 < D_0049B4D0) {
            D_003544A4 = D_0049B4D0;
        }
    }
    D_0049B4C4 = D_0049B4D0;
    return 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/code_12AB30", func_0012B080);
#endif

void func_0012B1B8(UnkObj *p) {
    f32 d;

    switch (D_0049B4D4) {
        case 3:
            if (D_0049B4D0 > 22.0f) {
                func_0012AE50(p);
                D_003596D0 = D_0049B4C8;
            }
            break;
        case 5:
            func_0012AE98(p, D_0049B4D0);
            D_003544A4 = D_0049B4D0;
            break;
        case 6:
            func_0012AE98(p, D_0049B4D0);
            D_003544A4 = D_0049B4D0;
            break;
        case 7:
            d = D_0049B4C8 - D_003596D0;
            if (ABS(d) > 3.0f) {
                func_0012AE98(p, D_0049B4D0);
                D_003544A4 = D_0049B4D0;
            }
            break;
    }
}
