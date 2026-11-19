#include "common.h"

/* tklib.c (name from the retail __FILE__ strings). Starts after the
 * handwritten VU0 module; 0x1305D0 is a guess for the start, since this
 * code shares the status struct with the POPSTATUS functions. Decompiled so
 * far: 0x1305D0-0x130FE8. */

typedef struct {
    /* 0x00 */ u16 unk0[6];
    /* 0x0C */ u8 unkC;
    /* 0x0D */ u8 unkD;
    /* 0x0E */ u8 padE[0x10 - 0xE];
    /* 0x10 */ u32 unk10;
    /* 0x14 */ u8 pad14[0x2A - 0x14];
    /* 0x2A */ u8 unk2A;
    /* 0x2B */ u8 unk2B;
    /* 0x2C */ u8 pad2C[0xB8 - 0x2C];
    /* 0xB8 */ u16 unkB8;
    /* 0xBA */ u16 unkBA;
    /* 0xBC */ u8 padBC[0xC0 - 0xBC];
    /* 0xC0 */ u16 unkC0[6];
    /* 0xCC */ u16 unkCC;
    /* 0xCE */ u16 unkCE;
} TkStatus;

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
extern s32 func_0033ED50(const char *, ...); /* printf */
extern void func_00125AA8(s32);
extern s32 func_00126F68(s32, s32, s32, s32);
extern void func_00125A40(s32, const char *, s32);
extern void func_00127188(s32, s32);
extern s32 func_00183628(void);
extern void func_00183610(s32);
extern TkStatus *func_001D0670(void);

extern u8 D_0049B7C0[];
extern s32 D_004AF800;
extern u8 D_0049B7A6;
extern u8 D_0049B7A5;
extern s32 D_0049B7A0;
extern u8 D_0049B7A4;
extern s32 D_0049B788;
extern s32 D_0049B790;
extern s32 D_0049B794;
extern s32 D_0049B798;
extern s32 D_0049B79C;

extern char *func_00100150(void); /* user name */
extern char *func_0034062C(char *, const char *); /* strcpy */
extern s32 func_0033C950(const char *); /* atoi */
extern s32 func_003404E8(const char *, const char *); /* strcmp */
extern void *func_0033EBE0(void *, s32, s32); /* memset */
extern s32 func_2068920(const char *); /* open */
extern s32 func_2068AF0(s32); /* file size */
extern s32 func_2068A78(s32, void *, s32); /* read */
extern s32 func_2068B58(s32); /* close */
extern s32 func_00348F50(s32);
extern void func_00348EF0(s32, s32);
extern char D_00359A70[];
extern s32 D_0049B780;
extern s32 D_0049B784;
extern s32 D_0049B78C;
extern s32 func_0031C5E8(void);
extern void func_206A088(void);
extern void func_00217838(void);
extern void func_0015E588(void);
extern void func_001B4D10(s32);
extern void func_00217FE8(void);
extern void func_0015DEA0(s32);
extern s32 func_001D08B0(void);
extern void func_0015DD50(void);
extern void func_0015DC90(void);
extern void func_001480D8(s32);
extern s32 func_00315218(void);
extern void func_206B6D0(void);
extern void func_003151F8(void);
extern void func_00317C00(void);
extern void func_003492E0(s32); /* FlushCache */
extern u32 *func_0031E5F0(s32);
extern void func_0031E940(u32 *, s32);
extern void func_0015DE50(void);
extern s32 func_2077300(s32, s32, s32);
extern void func_0015DD58(void);
extern s32 func_0031D4C8(s32, u16);
extern void func_2077590(s32);
extern void func_2073EB8(s32);
extern void func_2077698(void);
extern s32 func_2075F08(void);
extern void func_0015DD78(void);
extern void func_00315628(void);
extern void func_00315150(void);
extern void func_00153348(void);
extern void func_0031B848(void);
extern void func_00314EF8(s32, s32);
extern void func_00313918(void);
extern void func_20749C8(void);
extern void func_00321230(void);
extern void func_0031AE58(void);
extern void func_00217870(void);
extern void func_0015C090(const char *); /* debug marker */

/* File access interface returned by func_00172340. */
typedef struct {
    /* 0x00 */ s32 (*read)(s32 idx, void *buf, s32, s32);
    /* 0x04 */ s32 (*sector)(s32);
    /* 0x08 */ s32 (*sync)(s32);
    /* 0x0C */ void *unkC;
    /* 0x10 */ s32 (*open)(s32 grp);
    /* 0x14 */ s32 (*size)(s32 idx);
} TkFileIf;

extern TkFileIf *func_00172340(void);
extern void *D_00359A90;
extern void *D_00359A94;
extern s32 D_0049B7AC;
extern s32 D_0049B7B0;
extern s8 D_0048CEA1;
extern char *func_00340B10(char *, const char *, s32); /* strncpy */
extern s32 func_00340740(const char *); /* strlen */
extern s32 func_0033FF08(char *, const char *, ...); /* sprintf */
extern s32 func_00105830(void);
extern void func_0016DFD8(s32, s32, const char *, s32, s32);
extern void func_00315660(void);
extern void func_00314FD8(void);
extern void func_00315598(void);
extern void func_001757A8(char **);
extern void func_001741A8(s32);
extern void func_0016B4C0(s32);
extern void func_00319280(void *, s32);
extern void func_0031A7D0(s32);
extern void func_00254258(void *);
extern s32 func_002534E0(s32);
extern void func_002543E8(s32, s32);
extern void func_00253B78(void *, s32, s32);
extern void func_00253BF0(void *, s32, s32);
extern void func_0031A0B0(void);
extern void func_0031A028(s32);
extern char *func_00176868(s32);
extern void func_00253C68(char *);
extern void func_00253C98(char *);
extern s8 D_00473A58;

TkStatus *func_00130A40(void);
void func_00130A88(s32 a, s32 b);
s32 func_001312E0(s32 a, u16 b);

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

void func_00130718(TkStatus *p) {
    p->unkC0[0] = p->unk0[0];
    p->unkC0[1] = p->unk0[1];
    p->unkC0[2] = p->unk0[2];
    p->unkC0[3] = p->unk0[3];
    p->unkC0[4] = p->unk0[4];
    p->unkC0[5] = p->unk0[5];
    p->unkCC = p->unkC;
    p->unkCE = p->unkD;
}

void func_00130760(TkStatus *p) {
    p->unk2A = 1;
}

void func_00130770(TkStatus *p) {
    func_0033ED50("TK:===================================POPSTATUS\n");
    p->unk0[1] = p->unkC0[1];
    p->unkD = p->unkCE;
}

void func_001307B0(TkStatus *p) {
    func_0033ED50("TK:===================================POPMAPSTATUS\n");
    p->unk0[3] = p->unkC0[3];
    p->unk0[5] = p->unkC0[5];
}

u8 *func_001307F0(void) {
    return D_0049B7C0;
}

s32 func_00130800(void) {
    return D_004AF800;
}

void func_00130810(u8 v) {
    D_0049B7A6 = v;
}

u8 func_00130820(void) {
    return D_0049B7A6;
}

void func_00130830(u8 v) {
    D_0049B7A5 = v;
}

u8 func_00130840(void) {
    return D_0049B7A5;
}

s32 func_00130850(void) {
    return D_0049B7A0;
}

u8 func_00130860(void) {
    return func_00130A40()->unk2B;
}

void func_00130880(s32 v) {
    func_00130A40()->unk2B = v;
}

void func_001308A8(s32 v) {
    D_0049B7A4 = v != 0;
}

u8 func_001308B8(void) {
    return D_0049B7A4;
}

/* Round size up to a 2 KiB sector multiple. */
s32 func_001308C8(s32 size) {
    size = (size + 0x7FF) / 0x800 * 0x800;
    func_00125AA8(0x40);
    return func_00126F68(size, 3, 0, -1);
}

void func_00130920(void) {
    func_00125A40(0, "tklib.c", 406);
    func_00125A40(1, "tklib.c", 407);
}

void func_00130960(void) {
    func_00125A40(0, "tklib.c", 417);
    func_00125A40(1, "tklib.c", 418);
}

void func_001309A0(s32 a) {
    func_00127188(a, 3);
    func_00125A40(0, "tklib.c", 433);
    func_00125A40(1, "tklib.c", 434);
}

void func_001309E8(s32 bit, s32 on) {
    s32 v = func_00183628();

    if (on) {
        v |= 1 << bit;
    } else {
        v &= ~(1 << bit);
    }
    func_00183610(v);
}

TkStatus *func_00130A40(void) {
    return func_001D0670();
}

void func_00130A60(s32 v) {
    D_0049B788 = v;
}

void func_00130A70(s32 a, s32 b) {
    D_0049B790 = a;
    D_0049B794 = b;
}

void func_00130A88(s32 a, s32 b) {
    D_0049B798 = a;
    D_0049B79C = b;
}

s32 func_00130AA0(void) {
    return D_0049B790;
}

s32 func_00130AB0(void) {
    return D_0049B794;
}

s32 func_00130AC0(void) {
    return D_0049B798;
}

s32 func_00130AD0(void) {
    return D_0049B79C;
}

/* Parse the start-map file: lines of "<user> <a> <b>". '#' starts a
 * comment. The line for the current user sets func_00130A88(a, b). */
void func_00130AE0(u8 *s) {
    char key[0x200];
    char tok[0x1000];
    char *w = tok;
    s32 use = 1;
    s32 a = -1;
    s32 b = 0;
    s32 n = 0;
    s32 c;

    key[0] = '\0';
    func_0033ED50("TK:parse startmap info.:\n");
    if (func_00100150() == NULL) {
        return;
    }
    func_0033ED50("TK:Username:%s\n", func_00100150());
    while (1) {
        c = *s++;
        if (c == '\t' || c == ' ' || c == '\r' || c == '\n' || c == 0x1A || c == '\0') {
            if (w != tok) {
                *w = '\0';
                switch (n) {
                    case 0:
                        func_0034062C(key, tok);
                        break;
                    case 1:
                        a = func_0033C950(tok);
                        break;
                    case 2:
                        b = func_0033C950(tok);
                        break;
                }
                n++;
            }
            w = tok;
            tok[0] = '\0';
            if (c == '\r' || c == '\n' || c == 0x1A || c == '\0') {
                if (use && func_003404E8(key, func_00100150()) == 0 && a >= 0) {
                    func_00130A88(a, b);
                }
                use = 1;
                b = 0;
                a = -1;
                n = 0;
                w = tok;
                if (c == 0x1A) {
                    break;
                }
                if (c == '\0') {
                    break;
                }
            }
        } else {
            if (c == '#') {
                use = 0;
            }
            if (use) {
                *w++ = c;
            }
        }
    }
}

void func_00130CD8(void) {
    s32 fd = func_2068920(D_00359A70);
    s32 size; s32 len; void *buf;
    if (fd >= 0) {
        size = func_2068AF0(fd);
        len = size + 4;
        buf = (void *)func_001308C8(len);
        func_0033EBE0(buf, 0, len);
        func_2068A78(fd, buf, size);
        func_2068B58(fd);
        func_00130AE0(buf);
        func_001309A0((s32)buf);
    } else {
        func_0033ED50("TK:OPEN ERR\n");
    }
}

s32 func_00130D98(void) {
    return D_0049B780;
}

void func_00130DA8(s32 a, s32 b) {
    TkStatus *p = func_00130A40();

    p->unk0[3] = p->unk0[2];
    p->unk0[5] = p->unk0[4];
    if (p->unk2A) {
        func_001307B0(p);
    }
    p->unk0[4] = b;
    p->unk0[2] = a;
    p->unk2A = 0;
}

u16 func_00130E10(void) {
    return func_00130A40()->unk0[1];
}

u16 func_00130E30(void) {
    return func_00130A40()->unk0[3];
}

u16 func_00130E50(void) {
    return func_00130A40()->unk0[5];
}

u8 func_00130E70(void) {
    return func_00130A40()->unkD;
}

u16 func_00130E90(void) {
    return func_00130A40()->unk0[0];
}

u16 func_00130EB0(void) {
    return func_00130A40()->unk0[2];
}

u16 func_00130ED0(void) {
    return func_00130A40()->unk0[4];
}

u8 func_00130EF0(void) {
    return func_00130A40()->unkC;
}

/* Push a new map (a < 0: restore the saved one). */
void func_00130F10(s32 a, s32 b) {
    TkStatus *p = func_00130A40();
    s32 pop = a;

    if (pop < 0) {
        b = p->unkB8;
        a = p->unkBA;
        p->unkB8 = 0;
    }
    p->unkD = p->unkC;
    p->unk0[1] = p->unk0[0];
    p->unk0[0] = a;
    p->unkC = b;
    if (pop < 0) {
        func_00130770(p);
    }
    D_0049B784 = 1;
}

void func_00130F88(void) {
    D_0049B788 = 0;
    func_00130F10(-1, 0);
    D_0049B78C = 0;
}

void func_00130FB8(s32 a) {
    func_00348EF0(func_00348F50(a), a);
}

void func_00130FE8(void) {
    func_0033ED50("TK:Remove Scene\n");
    if (D_0049B78C) {
        if (func_0031C5E8() && D_0049B7A5) {
            func_0033ED50("TK:Output Encount\n");
            func_206A088();
        }
        func_0033ED50("TK:Remove Message Window\n");
        func_00217838();
        func_0033ED50("TK:Remove Message Window Done\n");
        func_0015E588();
        D_0049B78C = 0;
    } else {
        func_0033ED50("TK:No Event Initialize\n");
    }
    func_0033ED50("TK:Remove Scene Done\n");
}

u32 func_00131090(u32 a, u32 b) {
    return (a + b - 1) / b * b;
}

void func_001310B0(s32 scene) {
    func_001B4D10(scene);
    func_00217FE8();
    func_00217838();
    func_0033ED50("TK:Init Scene:%d\n", scene);
    func_00130FE8();
    func_0033ED50("TK:EventSetUp\n");
    func_0015DEA0(scene);
    D_0049B784 = 0;
    D_0049B78C = 1;
    D_0049B788 = 0;
    D_0049B7A0 = func_001D08B0();
}

void func_00131138(void) {
    func_0015DD50();
    D_0049B780 = 1;
}

s32 func_00131160(void) {
    return 0;
}

void func_00131168(void) {
    if (D_0049B784) {
        if (D_0049B788 <= 0) {
            func_001310B0(func_00130A40()->unk0[0]);
        } else {
            D_0049B788--;
        }
    }
    func_0015DC90();
    D_0049B780 = 0;
    func_00131138();
    func_001480D8(1);
    if (func_0031C5E8() && func_00315218()) {
        func_206B6D0();
        func_003151F8();
    }
    func_00317C00();
}

void func_00131200(void) {
    func_001312E0(0, 0);
}

void func_00131210(s32 a) {
    u32 *p;

    func_00131200();
    func_003492E0(0);
    __asm__ volatile("sync.l\n\tsync.p");
    p = func_0031E5F0(1);
    *p |= 0x40;
    func_0031E940(p, a);
}

void func_00131260(void) {
    s32 r;

    func_0015DE50();
    r = func_2077300(0, 0, 0);
    if (func_00130820()) {
        func_00131210(r);
        func_001312E0(0, 0);
    }
    func_00130810(0);
}

void func_001312C0(void) {
    func_0015DD58();
    func_00317C00();
}

s32 func_001312E0(s32 a, u16 b) {
    return func_0031D4C8(a, b);
}

void func_00131300(void) {
    if (func_0031C5E8()) {
        if (func_00315218()) {
            func_206B6D0();
            func_003151F8();
        }
        func_2077590(0);
        func_2073EB8(0);
        func_2077590(1);
        func_2073EB8(1);
        func_2077698();
        if (func_00130820()) {
            func_00131210(func_2075F08());
            func_001312E0(0, 0);
        }
        func_00131260();
    }
}

void func_001313A0(void) {
    func_0015DD78();
}

void func_001313A8(void) {
}

void func_001313B0(void) {
}

void func_001313B8(void) {
    func_00315628();
    func_00315150();
    func_00130F88();
    D_0049B780 = 1;
}

void func_001313F0(void) {
    func_00315150();
}

void func_001313F8(void) {
    func_001313F0();
    func_001313B8();
}

void func_00131418(void) {
    func_00153348();
    func_0031B848();
    func_00314EF8(-1, 0);
    func_00313918();
    if (func_0031C5E8()) {
        func_20749C8();
    }
    func_00321230();
    if (func_0031C5E8()) {
        func_0033ED50("TK:Disable Debug Font(S-JIS)\n");
        func_0031AE58();
        func_0033ED50("TK:Disable Debug Font(S-JIS) Done.\n");
    }
    func_00130FB8(0);
    func_00217870();
}

void *func_001314A8(s32 grp, s32 idx) {
    TkFileIf *f = func_00172340();
    u8 *buf;

    f->open(grp);
    buf = (u8 *)func_001308C8(f->size(idx));
    buf[0] = 0;
    buf[1] = 0;
    buf[2] = 0;
    buf[3] = 0;
    func_003492E0(0);
    f->read(idx, buf, 0, 0);
    f->sync(0);
    return buf;
}

void *func_00131548(s32 grp, s32 idx) {
    TkFileIf *f = func_00172340();
    s32 size;
    u8 *buf;

    f->open(grp);
    size = f->size(idx);
    func_0015C090("EVENT MALLOC");
    buf = (u8 *)func_001308C8(size);
    func_0015C090("EVENT MALLOC DONE");
    buf[0] = 0;
    buf[1] = 0;
    buf[2] = 0;
    buf[3] = 0;
    func_003492E0(0);
    func_0015C090("EVENT READ");
    f->read(idx, buf, 0, 0);
    func_0015C090("EVENT READ SYNC");
    f->sync(0);
    func_003492E0(0);
    return buf;
}

void func_00131628(s32 grp, s32 idx, void *buf) {
    TkFileIf *f = func_00172340();

    f->open(grp);
    f->size(idx);
    func_003492E0(0);
    f->read(idx, buf, 0, 0);
    f->sync(0);
    func_003492E0(0);
}

void func_001316B8(s32 grp, s32 idx, void *buf) {
    TkFileIf *f;

    func_0033ED50("TK:\tNonBlockRead:GRP=%d/IDX=%d/ADRS=%p\n", grp, idx, buf);
    f = func_00172340();
    f->open(grp);
    func_003492E0(0);
    f->read(idx, buf, 0, 0);
}

void func_00131748(s32 a) {
    func_00172340()->sync(a);
}

void *func_00131778(s32 grp, s32 idx, s32 min) {
    TkFileIf *f = func_00172340();
    s32 size;
    u8 *buf;

    f->open(grp);
    size = f->size(idx);
    buf = (u8 *)func_001308C8(size < min ? min : size);
    buf[0] = 0;
    buf[1] = 0;
    buf[2] = 0;
    buf[3] = 0;
    func_003492E0(0);
    f->read(idx, buf, 0, 0);
    f->sync(0);
    func_003492E0(0);
    return buf;
}

s32 func_00131838(s32 grp, s32 idx) {
    TkFileIf *f = func_00172340();

    f->open(grp);
    return f->size(idx);
}

void func_00131890(void) {
    D_00359A94 = func_001314A8(0x18, 4);
    func_0033ED50("TK:Read Event Mapinfo\n");
}

void func_001318C0(void) {
}

void func_001318C8(s32 v) {
    func_001306A0()[0xC] = v;
}

void func_001318F0(void) {
    D_0049B7AC = 0;
}

void func_00131900(void) {
    D_0049B7B0++;
    if (D_0049B7AC < 0x14C) {
        D_0049B7AC += 0x14;
    } else {
        D_0049B7AC = 0;
    }
}

void func_00131938(const char *s) {
    char name[0x20];
    char line[0x100];
    s32 n;

    if (((s8 *)func_001306A0())[0xC]) {
        func_0031D4C8(0, 0);
        func_00340B10(name, s, 0x17);
        for (n = func_00340740(s); n < 0x17; n++) {
            name[n] = ' ';
        }
        name[0x17] = '\0';
        func_0033FF08(line, "%04d:%s", D_0049B7B0, name);
        func_0016DFD8(0x30, D_0049B7AC + 0x20, line, func_00105830(), 1);
        func_00131900();
    }
}

void func_00131A20(void) {
    if (D_00359A90) {
        func_001309A0((s32)D_00359A90);
    }
    D_00359A90 = func_00131778(0x19, 0, 0x8000);
}

void func_00131A68(void) {
    TkStatus *p;

    func_001318F0();
    D_0049B7B0 = 0;
    func_00315660();
    func_00314FD8();
    func_00315598();
    D_0049B7A4 = 1;
    D_0049B7A5 = 0;
    D_00359A90 = 0;
    func_00130608(0);
    func_00130880(0);
    func_00130810(0);
    p = func_00130A40();
    p->unk10 = (p->unk10 | 0x2000000) & ~0x4000000;
}

void func_00131AF8(void) {
    func_0033ED50("TK:InitSa Callback:%d\n", 0);
    if (func_00130650()) {
        char *names[3] = {
            "\\FFXDEMO\\FFXDEMO.BIN;1",
            "\\FFXDEMO\\CDROM.MDG;1",
            "\\FFXDEMO\\CDROM.FID;1",
        };

        if (!D_0048CEA1) {
            func_0033ED50("DISCINFO 0:%s\n", names[0]);
            func_0033ED50("DISCINFO 1:%s\n", names[1]);
            func_0033ED50("DISCINFO 2:%s\n", names[2]);
            func_001757A8(names);
        }
    }
    func_001741A8(0);
    func_0033ED50("TK:sa_cd_callback_init\n");
    func_0016B4C0(0);
    func_0033ED50("TK:sa_cd_callback_init done\n");
    func_0033ED50("TK:InitSa Callback Done\n");
    func_00130A70(0x17, 0);
    func_00130A88(0x17, 0);
    D_00359A94 = 0;
    if (func_0031C5E8()) {
        func_0033ED50("TK:InitStartMap\n");
        func_00130CD8();
    }
}

void func_00131C00(void) {
    s32 size;
    void *buf;

    func_00131938("SHOUT 1");
    func_0033ED50("TK:TkInitReadSoundShoutFile\n");
    size = func_00131838(0x18, 5);
    buf = func_001314A8(0x18, 5);
    func_00131938("SHOUT 2");
    func_0033ED50("TK:Shout File:%p:%d:\n", buf, size);
    func_00319280(buf, size);
    func_00131938("SHOUT 3");
    func_0031A7D0(1);
    if (buf) {
        func_001309A0((s32)buf);
    }
    func_0033ED50("TK:TkInitReadSoundShoutFile Done\n");
    func_00131938("SHOUT 4");
}

void func_00131CC0(void) {
    s32 size;

    func_00131938("BATTLE MUSIC 1");
    func_0033ED50("TK:TkInitReadSoundBattleMusicFile\n");
    size = func_00131838(0x26, 0xE);
    func_0033ED50("TK:Read Battle Music File(no:%d size:%d)\n", 0xE, size);
    if (size > 0x7FFF) {
        func_0033ED50("TK:!!!!!!!!!!!!!!!!!!!!!!!!!!!! Battle Music Score too large.!!!!!!!!!!!!!!!!!!!!!!!!!!!! \n");
    }
    func_00131938("BATTLE MUSIC 2");
    func_00131628(0x26, 0xE, func_001307F0());
    D_004AF800 = size;
    func_0033ED50("TK:TkInitReadSoundBattleMusicFile Done\n");
}

void func_00131D68(void) {
    void *buf;

    func_00131938("SND SAVE INIT");
    func_00131838(0x18, 0);
    buf = func_001314A8(0x18, 0);
    func_00131938("SND BLOCK");
    func_00254258(buf);
    func_00131938("SND BLOCK1");
    func_0031A7D0(1);
    func_002534E0(1);
    func_00131938("SEND SYNC DONE");
    func_001309A0((s32)buf);
}

void func_00131DF0(void) {
    s32 i;

    func_00131938("SND SAVE STB");
    func_0033ED50("TK:TkInitSoundSave\n");
    for (i = 0; i < 0x62; i++) {
        func_002543E8(i, 1);
        func_002534E0(1);
    }
    func_00131938("SND SAVE STB DONE");
    func_0033ED50("TK:TkInitSoundSave Done\n");
}

void func_00131E68(s32 load) {
    void *buf;
    s32 size;
    s32 sector;
    TkFileIf *f;

    if (D_0048CEA1) {
        return;
    }
    func_00131938("INIT WAVE INFO READ FILE");
    if (load) {
        buf = func_001314A8(0x2C, 1);
        size = func_00131838(0x2C, 1);
    } else {
        buf = 0;
        size = 0;
    }
    func_00131938("INIT WAVE REGIST WAVE");
    f = func_00172340();
    f->open(0x2C);
    sector = f->sector(0);
    func_0033ED50("TK:Sound Get Sector Pos:%d\n", sector);
    func_00131938("INIT WAVE TRANS TO IOP");
    func_00253B78(buf, size, sector);
    func_00131938("INIT WAVE TRANS DONE");
    if (buf) {
        func_001309A0((s32)buf);
    }
}

void func_00131F60(s32 load) {
    void *buf;
    s32 size;
    s32 sector;
    TkFileIf *f;

    if (D_0048CEA1) {
        return;
    }
    func_00131938("MUSIC INFO READ FILE");
    if (load) {
        buf = func_001314A8(0x2D, 1);
        size = func_00131838(0x2D, 1);
    } else {
        buf = 0;
        size = 0;
    }
    f = func_00172340();
    f->open(0x2D);
    sector = f->sector(0);
    func_0033ED50("TK:Sound Music Get Sector Pos:%d\n", sector);
    func_00131938("MUSIC INFO TRANS TO IOP");
    func_00253BF0(buf, size, sector);
    func_00131938("MUSIC INFO TRANS DONE");
    if (buf) {
        func_001309A0((s32)buf);
    }
}

void func_00132048(void) {
    func_00131938("SND INIT");
    func_0031A0B0();
    func_00131938("WAVE INFO");
    func_00131E68(1);
    func_00131938("WAVE WITH SET");
    func_0031A028(0);
    func_00131938("SOUND SAVE");
    func_00131D68();
    func_00131938("SOUND SAVE 2");
    func_00131DF0();
    func_00131938("MUSIC INFO");
    func_00131F60(1);
    func_00131938("SHOUT");
    func_00131C00();
    func_00131938("BATTLE");
    func_00131CC0();
}

void func_001320F8(void) {
    char *name = "";

    func_0033ED50("TK:TkInitWaveInfoHdd\n");
    if (D_00473A58) {
        name = func_00176868(0x2C);
    }
    func_0033ED50("TK:HDD/WaveFilename:%s\n", name);
    func_00253C68(name);
    name = "";
    func_0033ED50("TK:TkInitSoundSetWaveInfo Done.\n");
    func_0033ED50("TK:TkInitMusicInfoHdd\n");
    if (D_00473A58) {
        name = func_00176868(0x2D);
    }
    func_0033ED50("TK:HDD/MusicFilename:%s\n", name);
    func_00253C98(name);
    func_0033ED50("TK:TkInitSoundSetMusicInfo Done.\n");
}

void func_001321C0(void) {
    func_00131E68(0);
}

void func_001321C8(void) {
    func_001321C0();
}
