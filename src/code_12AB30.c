#include "common.h"

/* Provisional translation unit: real file boundaries not yet known. */

typedef struct {
    /* 0x00 */ s32 unk0[3];
    /* 0x0C */ s32 unkC;
} Unk3596B0; /* size = 0x10 */

extern Unk3596B0 *D_003596B0;
extern s32 D_0049B460[];
extern s32 D_0035473C;
extern s32 D_0049B4B4;
extern s32 D_0049B4B8;
extern s32 D_0049B4BC;
extern s32 D_0049B4C0;

extern void func_00117160(void *, f32);
extern void func_001176E8(void *, f32);
extern void func_00117838(void *);
extern void func_0011BD10(void *, s32);
extern f32 func_0011D748(s32);
f32 func_0012AC70(void *, s32, s32);

s32 func_0012AB30(s32 i) {
    s32 v = D_003596B0[i].unkC & 0x7F;

    if ((u32)(v - 0x30) < 0x10) {
        return D_0049B460[v - 0x30];
    }
    return v;
}

INCLUDE_ASM("asm/nonmatchings/code_12AB30", func_0012AB78);

INCLUDE_ASM("asm/nonmatchings/code_12AB30", func_0012AC70);

void func_0012AD98(void *p) {
    func_0012AC70(p, D_0049B4B4, D_0049B4B8);
    func_00117160(p, func_0011D748(2));
    func_0011BD10(p, 1);
}

s32 func_0012ADE8(s8 *p) {
    s32 r = 0;

    if (D_0035473C & 0x40) {
        r = p[0x198] != 1;
    }
    return r;
}

void func_0012AE10(void *p) {
    func_00117838(p);
    func_00117160(p, func_0011D748(2));
    func_0011BD10(p, 1);
}

void func_0012AE50(void *p) {
    func_001176E8(p, func_0012AC70(p, D_0049B4BC, D_0049B4C0));
    func_0011BD10(p, 4);
}
