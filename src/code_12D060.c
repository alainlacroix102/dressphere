#include "common.h"
#include "list.h"

/* Provisional translation unit: starts at 0x12D060 (the rodata after
 * map_id.c's begins here with the /ffx2/proj/map/... loader paths); the
 * end is not known yet. */

typedef struct {
    s32 x, y, z, w;
} __attribute__((aligned(16))) IVec4;

typedef struct {
    /* 0x000 */ u8 pad0[0x10];
    /* 0x010 */ f32 unk10[4];
    /* 0x020 */ u8 pad20[0x150 - 0x20];
    /* 0x150 */ f32 unk150;
    /* 0x154 */ u8 pad154[4];
    /* 0x158 */ s8 unk158;
    /* 0x159 */ u8 pad159[0x160 - 0x159];
    /* 0x160 */ f32 unk160[4];
    /* 0x170 */ f32 unk170[4];
    /* 0x180 */ f32 unk180;
    /* 0x184 */ s32 unk184;
    /* 0x188 */ s8 unk188;
    /* 0x189 */ s8 unk189;
} Unk12E760;

extern s8 D_0049B728;
extern s32 D_003596DC;
extern s32 D_00359708;
extern char D_0047B3E8[]; /* "result=%d\n" */

extern void func_00320CD8(IVec4 *out, void *v, void *m, s32);
extern s32 func_0012DD58(f32 *, f32 *, f32 *, f32 *, s32);
extern s32 func_0033ED50(const char *, ...); /* printf */

void func_0012D060(s8 v) {
    D_0049B728 = v;
}

s8 func_0012D070(void) {
    return D_0049B728;
}

void func_0012D080(void) {
}

INCLUDE_ASM("asm/nonmatchings/code_12D060", func_0012D088);

/* Project a point; fails (1) if it is behind the camera or off screen. */
s32 func_0012D2B8(IVec4 *out, void *m, void *v) {
    IVec4 s;

    func_00320CD8(&s, v, m, 0);
    if (s.z < 0) {
        return 1;
    }
    if (s.x < 0x6600) {
        return 1;
    }
    if (s.x > 0x9A00) {
        return 1;
    }
    if (s.y < 0x7000) {
        return 1;
    }
    if (s.y > 0x9000) {
        return 1;
    }
    s.w = 0;
    *(u128 *)out = *(u128 *)&s;
    return 0;
}

void func_0012D350(void) {
    D_003596DC = (D_003596DC + 1) & 1;
}

INCLUDE_ASM("asm/nonmatchings/code_12D060", func_0012D368);

INCLUDE_ASM("asm/nonmatchings/code_12D060", func_0012D6A8);

INCLUDE_ASM("asm/nonmatchings/code_12D060", func_0012DA38);

void func_0012DBE8(void) {
}

INCLUDE_ASM("asm/nonmatchings/code_12D060", func_0012DBF0);

INCLUDE_ASM("asm/nonmatchings/code_12D060", func_0012DD58);

INCLUDE_ASM("asm/nonmatchings/code_12D060", func_0012E0A0);

#ifdef NON_MATCHING
/* Debug test, runs once. Retail stores the 0.0f components with
 * `mtc1 $0,$f0; swc1` (ours: `sw $0`), which also shifts the scheduling. */
void func_0012E468(void) {
    f32 a[4];
    f32 b[4];
    f32 c[4];
    f32 d[4];
    s32 r;

    if (D_00359708 == 0) {
        D_00359708 = 1;
        a[0] = 10.0f;
        a[1] = 0.0f;
        a[2] = 10.0f;
        b[0] = 20.0f;
        b[1] = 0.0f;
        b[2] = 20.0f;
        c[0] = 10.0f;
        c[1] = 0.0f;
        c[2] = 20.0f;
        d[0] = 20.0f;
        d[1] = 0.0f;
        d[2] = 10.0f;
        r = func_0012DD58(a, b, c, d, 1);
        func_0033ED50(D_0047B3E8, r);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/code_12D060", func_0012E468);
#endif

INCLUDE_ASM("asm/nonmatchings/code_12D060", func_0012E500);

void func_0012E6E0(ListNode *n) {
    ListRemove(&D_00359710, n);
}

static inline void SetVec3(f32 *v, f32 x, f32 y, f32 z) {
    v[0] = x;
    v[1] = y;
    v[2] = z;
    v[3] = 1.0f;
}

void func_0012E760(Unk12E760 *p, f32 x, f32 y, f32 z) {
    SetVec3(p->unk10, x, y, z);
}

void func_0012E780(Unk12E760 *p, f32 v) {
    p->unk150 = v;
}

typedef struct {
    f32 v[4];
} __attribute__((aligned(8))) Vec4Copy;

void func_0012E788(Unk12E760 *p, s8 a, f32 x, f32 y, f32 z, f32 w) {
    *(Vec4Copy *)p->unk160 = *(Vec4Copy *)p->unk10;
    SetVec3(p->unk170, x, y, z);
    p->unk189 = 1;
    p->unk180 = w;
    p->unk188 = a;
    p->unk184 = 0;
}

void func_0012E7D0(Unk12E760 *p, s8 v) {
    p->unk158 = v;
}

void func_0012E7D8(void) {
    ListClear(&D_00359710);
}
