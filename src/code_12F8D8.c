#include "common.h"
#include "list.h"

/* Provisional translation unit 0x12F8D8-0x12F9D4. func_0012F8D8 repeats
 * code_12D060's func_0012E7D8, so a file boundary lies between them. */

typedef struct {
    /* 0x000 */ u8 pad0[0x18C];
    /* 0x18C */ f32 unk18C;
} Unk12F9A8;

void func_0012F8D8(void) {
    ListClear(&D_00359710);
}

void func_0012F988(void) {
    D_00359710.head = NULL;
    D_00359710.count = 0;
    D_00359710.cur = NULL;
    D_00359710.unk8 = 0;
}

void func_0012F9A8(Unk12F9A8 *p, f32 v) {
    p->unk18C = v;
}

void func_0012F9B0(f32 *v, f32 s) {
    v[2] = s;
    v[1] = s;
    v[0] = s;
}

f32 *func_0012F9C0(f32 *v, f32 x, f32 y, f32 z) {
    v[0] = x;
    v[1] = y;
    v[2] = z;
    return v;
}
