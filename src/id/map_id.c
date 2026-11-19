#include "common.h"

/* src/id/map_id.c: map/event IDs (name from the retail assert strings).
 * The file starts at 0x12BCB0. Where it ends is not known yet; only the
 * start is decompiled so far. */

#define MAPID_EVENT1 0x30
#define MAPID_EVENT16 0x3F

/* Assert handler: (level, expression, file, line, message, caller). */
extern void func_0012A130(s32, const char *, const char *, s32, const char *, void *);
extern void func_0012A1B8(const char *, ...); /* debug printf */

/* Read our own return address into `ra` (retail goes through $t7). */
#define GET_RA(ra)                                                    \
    {                                                                 \
        register void **_p __asm__("$15") = &(ra);                    \
        __asm__ volatile("sw $31,0(%0)" : : "r"(_p) : "memory");      \
    }

/* No do/while(0) wrapper: its loop notes make gcc align the next label. */
#define SG_ASSERT(cond, line, msg)                                       \
    if (!(cond)) {                                                      \
        void *_ra;                                                      \
        GET_RA(_ra);                                                    \
        func_0012A130(1, #cond, "src/id/map_id.c", line, msg, _ra);     \
    }

typedef struct {
    /* 0x000 */ u8 pad0[0x1A1];
    /* 0x1A1 */ s8 unk1A1;
    /* 0x1A2 */ u8 pad1A2[0x1A8 - 0x1A2];
    /* 0x1A8 */ u64 unk1A8;
    /* 0x1B0 */ u8 pad1B0[0x854 - 0x1B0];
    /* 0x854 */ s32 unk854;
} MapIdObj;

extern s32 D_0049B460[20]; /* event IDs; [0..15] = MAPID_EVENT1..16 */
extern u8 D_0049B4E0[2][4];
extern s8 D_0049B4E8;

void func_0012BE38(s32 index);
s32 func_0012BE28(MapIdObj *p);

void Sg_IdSetEventID(s32 index, s32 id) {
    SG_ASSERT(MAPID_EVENT1<=index && index <=MAPID_EVENT16, 1023,
              "Sg_IdSetEventID:EventID\x82\xccindex\x8ew\x92\xe8\x82\xaa\x96\xb3\x8c\xf8\x82\xc5\x82\xb7\x81" "B");
    D_0049B460[index - MAPID_EVENT1] = id;
}

s32 Sg_IdGetEventID(s32 index) {
    SG_ASSERT(MAPID_EVENT1<=index && index <=MAPID_EVENT16, 1028,
              "Sg_IdGetEventID:EventID\x82\xccindex\x8ew\x92\xe8\x82\xaa\x96\xb3\x8c\xf8\x82\xc5\x82\xb7\x81" "B");
    return D_0049B460[index - MAPID_EVENT1];
}

void func_0012BD98(void) {
    s32 i;

    func_0012A1B8("EventId Dump:\n");
    for (i = 0; i < 16; i++) {
        func_0012A1B8("EventId[%d]=%x\n", i + 1, D_0049B460[i]);
    }
    func_0012A1B8("--------------\n");
}

void func_0012BE18(MapIdObj *p) {
    p->unk854 = 0xFFFE0000;
}

s32 func_0012BE28(MapIdObj *p) {
    return (p->unk854 >> 9) & 3;
}

void func_0012BE38(s32 index) {
    SG_ASSERT(index==0 || index==1, 1057, NULL);
    D_0049B4E8 = index;
}

void func_0012BE98(s32 index, s32 v) {
    SG_ASSERT(index <= 3, 1062, NULL);
    D_0049B4E0[D_0049B4E8][index] = v;
}

s32 func_0012BF18(MapIdObj *p) {
    if (p->unk1A1 == 2) {
        if ((p->unk1A8 >> 61) & 1) {
            return 8;
        }
        return 9;
    }
    return D_0049B4E0[D_0049B4E8][func_0012BE28(p)];
}

void func_0012BF80(void) {
    s32 i;

    for (i = 19; i >= 0; i--) {
        D_0049B460[i] = 0;
    }
    for (i = 0; i < 4; i++) {
        D_0049B4E0[0][i] = 0;
        D_0049B4E0[1][i] = 0;
    }
    func_0012BE38(0);
}
