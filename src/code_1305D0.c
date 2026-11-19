#include "common.h"

/* Provisional translation unit 0x1305D0-0x130770: follows the handwritten
 * VU0 module. Mostly getters and setters. */

typedef struct {
    /* 0x00 */ u16 unk0[6];
    /* 0x0C */ u8 unkC;
    /* 0x0D */ u8 unkD;
    /* 0x0E */ u8 padE[0x2A - 0xE];
    /* 0x2A */ u8 unk2A;
    /* 0x2B */ u8 pad2B[0xC0 - 0x2B];
    /* 0xC0 */ u16 unkC0[6];
    /* 0xCC */ u16 unkCC;
    /* 0xCE */ u16 unkCE;
} Unk130718;

extern u8 D_0049B7A8;
extern u8 D_0049B7A7;
extern u8 D_004761C6;
extern u8 D_004761C7;
extern u8 D_004761C8;
extern u8 D_00359A8E;
extern u8 D_004AB800[];
extern u8 D_004AB7C0[];

extern s32 func_0031C688(void);
extern void func_0031C738(void);
extern void func_001DFF58(s32);
extern void func_002171C0(s32);
extern void func_001DFFB0(void);

void func_001305D0(void) {
    D_0049B7A8 = (u8)func_0031C688();
}

u8 func_001305F8(void) {
    return D_0049B7A8;
}

void func_00130608(u8 v) {
    D_0049B7A7 = v;
}

u8 func_00130618(void) {
    return D_0049B7A7;
}

u8 *func_00130628(void) {
    return D_004AB800;
}

void func_00130638(u8 v) {
    D_004761C6 = v;
}

void func_00130648(void) {
    func_0031C738();
}

u8 func_00130650(void) {
    return D_004761C6;
}

void func_00130660(u8 v) {
    D_004761C7 = v;
}

u8 func_00130670(void) {
    return D_004761C7;
}

void func_00130680(u8 v) {
    D_004761C8 = v;
}

u8 func_00130690(void) {
    return D_004761C8;
}

u8 *func_001306A0(void) {
    return D_004AB7C0;
}

void func_001306B0(s32 id) {
    func_001DFF58(id);
    if ((u32)(id - 0x700A) < 0x1A) {
        func_002171C0(id - 0x700A);
    }
}

void func_001306F0(void) {
    func_001DFFB0();
}

/* Read and clear. */
u8 func_001306F8(void) {
    u8 v = D_00359A8E;

    D_00359A8E = 0;
    return v;
}

u8 func_00130708(void) {
    return D_00359A8E;
}

void func_00130718(Unk130718 *p) {
    p->unkC0[0] = p->unk0[0];
    p->unkC0[1] = p->unk0[1];
    p->unkC0[2] = p->unk0[2];
    p->unkC0[3] = p->unk0[3];
    p->unkC0[4] = p->unk0[4];
    p->unkC0[5] = p->unk0[5];
    p->unkCC = p->unkC;
    p->unkCE = p->unkD;
}

void func_00130760(Unk130718 *p) {
    p->unk2A = 1;
}
