#include "common.h"

/* Provisional translation unit: event-script command handlers.
 * Each handler takes (script context, opcode?, argument stream) and pops
 * its arguments with func_0014A470 (int) or func_0014A538 (float). */
/* eecc-asflags: -G0 */

typedef struct {
    /* 0x00 */ u8 pad0[0x2E];
    /* 0x2E */ u16 unk2E;
} ScriptCtx;

/* One of 32 entries at +0xA4 in the object from func_00147A80. */
typedef struct {
    /* 0x0 */ u8 x;
    /* 0x1 */ u8 y;
    /* 0x2 */ u16 id;
    /* 0x4 */ s32 value;
} ScriptMarker;

extern s32 func_0014A470(ScriptCtx *, void *); /* pop int */
extern f32 func_0014A538(ScriptCtx *, void *); /* pop float */
extern s32 func_00315CD8(f32);
extern s32 func_00315D48(f32);
extern s32 func_00315DB8(s32);
extern s32 func_00315DF8(s32);
extern u8 *func_00147A80(void);
extern s32 func_00315668(f32);
extern s32 func_00315688(f32);
extern s32 func_003156A8(f32);
extern f32 func_0032BB78(f32);
extern f32 func_0032CCA8(f32, f32);
extern f32 sqrtf(f32);
extern s32 func_00315930(s32);
extern s32 func_00315950(s32);
extern s32 func_00315970(f32, f32, f32, f32);

s32 func_00132918(ScriptCtx *ctx, s32 op, void *args) {
    return func_0014A470(ctx, args);
}

s32 func_00132938(ScriptCtx *ctx, s32 op, void *args) {
    return func_0014A470(ctx, args) << 15;
}

s32 func_00132958(ScriptCtx *ctx, s32 op, void *args) {
    return func_0014A538(ctx, args) * 32768.0f;
}

s32 func_00132988(ScriptCtx *ctx, s32 op, void *args) {
    return func_00315CD8(func_0014A538(ctx, args));
}

s32 func_001329B0(ScriptCtx *ctx, s32 op, void *args) {
    return func_00315D48(func_0014A538(ctx, args));
}

s32 func_001329D8(ScriptCtx *ctx, s32 op, void *args) {
    return func_00315DB8(func_0014A470(ctx, args));
}

s32 func_00132A00(ScriptCtx *ctx, s32 op, void *args) {
    return func_00315DF8(func_0014A470(ctx, args));
}

s32 func_00132A28(ScriptCtx *ctx, s32 op, void *args) {
    s32 value = func_0014A470(ctx, args);
    s32 y = func_0014A470(ctx, args);
    s32 x = func_0014A470(ctx, args);
    s32 i = func_0014A470(ctx, args);
    ScriptMarker *m;

    i = i < 0 ? 0 : (i < 0x20 ? i : 0x1F);
    m = (ScriptMarker *)(func_00147A80() + 0xA4) + i;
    if (x < 0 || y < 0) {
        m->x = 0;
        m->y = 0;
    } else {
        x /= 8;
        y /= 4;
        m->x = (x & 0x3F) | 0x80;
        m->y = y & 0x7F;
        m->value = value;
        m->id = ctx->unk2E;
    }
    return 1;
}

s32 func_00132B30(ScriptCtx *ctx, s32 op, void *args) {
    return func_00315668(func_0014A538(ctx, args));
}

s32 func_00132B58(ScriptCtx *ctx, s32 op, void *args) {
    return func_00315688(func_0014A538(ctx, args));
}

s32 func_00132B80(ScriptCtx *ctx, s32 op, void *args) {
    return func_003156A8(func_0014A538(ctx, args));
}

f32 func_00132BA8(ScriptCtx *ctx, s32 op, void *args) {
    return func_0032BB78(func_0014A538(ctx, args));
}

f32 func_00132BD0(ScriptCtx *ctx, s32 op, void *args) {
    f32 x = func_0014A538(ctx, args);
    f32 y = func_0014A538(ctx, args);

    return func_0032CCA8(y, x);
}

f32 func_00132C28(ScriptCtx *ctx, s32 op, void *args) {
    f32 v = func_0014A538(ctx, args);

    return sqrtf(v);
}

f32 func_00132C70(ScriptCtx *ctx, s32 op, void *args) {
    f32 v = func_0014A538(ctx, args);

    return 1.0f / sqrtf(v);
}

s32 func_00132CC8(ScriptCtx *ctx, s32 op, void *args) {
    return func_00315930(func_0014A470(ctx, args));
}

s32 func_00132CF0(ScriptCtx *ctx, s32 op, void *args) {
    return func_00315950(func_0014A470(ctx, args));
}

s32 func_00132D18(ScriptCtx *ctx, s32 op, void *args) {
    f32 d = func_0014A538(ctx, args);
    f32 c = func_0014A538(ctx, args);
    f32 b = func_0014A538(ctx, args);
    f32 a = func_0014A538(ctx, args);

    return func_00315970(a, b, c, d);
}
