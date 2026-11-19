#include "common.h"

/* src/id/map_id.c: map/event IDs (name from the retail assert strings).
 * 0x12BCB0-0x12D060; the next file's rodata is the sugi map paths. */

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

extern void func_00189D78(s32, const char *, const char *); /* error report */
extern void func_0012A370(void *);
extern s32 func_00336D60(s32);
extern char *func_0034062C(char *, const char *); /* strcpy */
extern char *func_00106240(s32);
extern s32 func_00106268(s32);
extern void func_001061C8(s32, char *);
extern void func_00106148(s32, s32);
extern void func_001009A0(s32);
extern f32 sqrtf(f32);

typedef struct {
    /* 0x0 */ u8 pad0[0xC];
    /* 0xC */ s32 unkC;
} MapIdEntry; /* size = 0x10 */

typedef struct {
    /* 0x00 */ s32 base;    /* address the data was built for */
    /* 0x04 */ s16 version;
    /* 0x06 */ s16 count;
    /* 0x08 */ u8 pad8[0x18 - 0x8];
    /* 0x18 */ s32 unk18;   /* pointer, relocated on load */
    /* 0x1C */ MapIdEntry *entries;
} MapIdHeader;

typedef struct {
    /* 0x00 */ u8 pad0[0x18];
    /* 0x18 */ f32 unk18;
} MapIdSortItem;

extern s32 D_0049B460[20]; /* event IDs; [0..15] = MAPID_EVENT1..16 */
extern u8 D_0049B4E0[2][4];
extern s8 D_0049B4E8;
extern MapIdSortItem *D_0049B4F0[];
extern s8 D_0049B598;
extern s8 D_003596B4;
extern s32 D_003596D4;
extern s32 D_003596D8;
extern s8 D_00473A54;
extern char D_0049B5A0[3][64];
extern char D_0049B660[3][64];

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

INCLUDE_ASM("asm/nonmatchings/id/map_id", func_0012BFE0);

f32 func_0012C2B0(f32 *from, f32 *to) {
    f32 d[3];

    d[0] = to[0] - from[0];
    d[2] = to[2] - from[2];
    return sqrtf(d[0] * d[0] + d[2] * d[2]);
}

INCLUDE_ASM("asm/nonmatchings/id/map_id", func_0012C318);

/* Selection sort of D_0049B4F0[0..n) by unk18, ascending. */
void func_0012C648(s32 n) {
    s32 i;
    s32 j;
    s32 min;
    MapIdSortItem *tmp;

    for (i = 0; i < n; i++) {
        min = i;
        for (j = i; j < n; j++) {
            if (D_0049B4F0[min]->unk18 >= D_0049B4F0[j]->unk18) {
                min = j;
            }
        }
        tmp = D_0049B4F0[i];
        D_0049B4F0[i] = D_0049B4F0[min];
        D_0049B4F0[min] = tmp;
    }
}

void func_0012C6F8(s32 id, s32 v) {
    if (id == 0x1113) {
        D_003596B4 = v;
    } else {
        func_00336D60(0);
    }
}

INCLUDE_ASM("asm/nonmatchings/id/map_id", func_0012C718);

s16 func_0012CCB0(u32 w) {
    s16 col = func_0012CD10() ? w >> 17 : 0x4210;

    return col;
}

s16 func_0012CCE0(MapIdObj *p) {
    u32 w = p->unk854;
    s16 col = func_0012CD10() ? w >> 17 : 0x4210;

    return col;
}

s8 func_0012CD10(void) {
    return D_0049B598;
}

void Sg_IdInit(MapIdHeader *h) {
    s32 off;
    s32 i;

    if (h == NULL) {
        func_0012A370(NULL);
        return;
    }
    if (h->version < 0x723) {
        func_00189D78(0, "Sg_IdInit", "SG:MapID Version Error!");
    }
    D_0049B598 = h->version > 0x1202;
    off = (s32)h - h->base;
    if (off != 0) {
        h->base = off;
        h->entries = (MapIdEntry *)((s32)h->entries + off);
        h->unk18 += off;
        for (i = 0; i < h->count; i++) {
            h->entries[i].unkC += off;
        }
    }
    func_0012A370(h);
}

void func_0012CE00(MapIdHeader *h) {
    Sg_IdInit(h);
}

s32 func_0012CE08(void) {
    D_003596D4++;
    if (D_003596D4 >= 4) {
        D_003596D4 = 0;
    }
    return D_003596D4;
}

void func_0012CE30(void) {
    func_0012A370(NULL);
}

void func_0012CE38(void) {
    char *s;

    if (!D_00473A54) {
        func_001009A0(1);
        return;
    }
    if ((s = func_00106240(5))) {
        func_0034062C(D_0049B660[0], s);
    }
    if ((s = func_00106240(7))) {
        func_0034062C(D_0049B660[1], s);
    }
    if ((s = func_00106240(6))) {
        func_0034062C(D_0049B5A0[0], s);
    }
    if ((s = func_00106240(8))) {
        func_0034062C(D_0049B5A0[1], s);
    }
    if ((s = func_00106240(0xC))) {
        func_0034062C(D_0049B660[2], s);
    }
    if ((s = func_00106240(0xD))) {
        func_0034062C(D_0049B5A0[2], s);
    }
    func_001009A0(1 - func_00106268(9));
}

void func_0012CF20(void) {
    func_001061C8(5, D_0049B660[0]);
    func_001061C8(7, D_0049B660[1]);
    func_001061C8(6, D_0049B5A0[0]);
    func_001061C8(8, D_0049B5A0[1]);
    func_001061C8(0xC, D_0049B660[2]);
    func_001061C8(0xD, D_0049B5A0[2]);
}

void func_0012CF98(s32 v) {
    D_003596D8 = v;
    func_00106148(0xE, v);
}

s32 func_0012CFB0(void) {
    return D_003596D8;
}

char *func_0012CFC0(s32 which) {
    if (which) {
        return D_0049B5A0[D_003596D8];
    }
    return D_0049B660[D_003596D8];
}

void func_0012CFF8(const char *src, s32 which) {
    if (which) {
        func_0034062C(D_0049B5A0[D_003596D8], src);
    } else {
        func_0034062C(D_0049B660[D_003596D8], src);
    }
    func_0012CF20();
}
