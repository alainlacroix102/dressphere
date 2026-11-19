#include "common.h"

/* tklib.c (name from the retail __FILE__ strings). Starts after the
 * handwritten VU0 module; 0x1305D0 is a guess for the start, since this
 * code shares the status struct with the POPSTATUS functions. Decompiled so
 * far: 0x1305D0-0x130FE8. */

/* FFXCONFIG block (0x40 bytes) at D_004AB7C0. */
typedef struct {
    /* 0x00 */ u8 pad0[8];
    /* 0x08 */ s8 unk8;  /* printf */
    /* 0x09 */ s8 unk9;  /* menu debug */
    /* 0x0A */ s8 unkA;  /* cd read */
    /* 0x0B */ s8 unkB;  /* DVD printf cut */
    /* 0x0C */ s8 unkC;  /* yi assert (on-screen log) */
    /* 0x0D */ s8 unkD;  /* music mute */
    /* 0x0E */ s8 unkE;  /* boot type */
    /* 0x0F */ s8 unkF;  /* movie read */
    /* 0x10 */ s8 unk10; /* thread mode */
    /* 0x11 */ u8 unk11[8];
    /* 0x19 */ u8 pad19[0x40 - 0x19];
} FfxConfig;

typedef struct {
    /* 0x000 */ u16 unk0[6];
    /* 0x00C */ u8 unkC;
    /* 0x00D */ u8 unkD;
    /* 0x00E */ u16 unkE;
    /* 0x010 */ u32 unk10;
    /* 0x014 */ s32 unk14;
    /* 0x018 */ s32 unk18;
    /* 0x01C */ s32 unk1C;
    /* 0x020 */ u8 unk20;
    /* 0x021 */ u8 unk21;
    /* 0x022 */ u8 unk22;
    /* 0x023 */ u8 unk23;
    /* 0x024 */ s32 unk24;
    /* 0x028 */ u8 unk28;
    /* 0x029 */ u8 unk29;
    /* 0x02A */ u8 unk2A;
    /* 0x02B */ u8 unk2B;
    /* 0x02C */ s32 unk2C[8];
    /* 0x04C */ s32 unk4C[20];
    /* 0x09C */ u8 pad9C[0xAC - 0x9C];
    /* 0x0AC */ u8 unkAC[8];
    /* 0x0B4 */ u16 unkB4;
    /* 0x0B6 */ u16 unkB6;
    /* 0x0B8 */ u16 unkB8;
    /* 0x0BA */ u16 unkBA;
    /* 0x0BC */ u8 padBC[0xC0 - 0xBC];
    /* 0x0C0 */ u16 unkC0[6];
    /* 0x0CC */ u16 unkCC;
    /* 0x0CE */ u16 unkCE;
    /* 0x0D0 */ u8 unkD0;
    /* 0x0D1 */ u8 padD1;
    /* 0x0D2 */ u8 unkD2;
    /* 0x0D3 */ u8 unkD3;
    /* 0x0D4 */ u16 unkD4;
    /* 0x0D6 */ u8 unkD6;
    /* 0x0D7 */ u8 unkD7;
    /* 0x0D8 */ u8 padD8[0xE4 - 0xD8];
    /* 0x0E4 */ s32 unkE4;
    /* 0x0E8 */ u16 unkE8;
    /* 0x0EA */ u16 unkEA;
    /* 0x0EC */ u8 unkEC;
    /* 0x0ED */ u8 padED[0x10C - 0xED];
    /* 0x10C */ s32 unk10C[56];
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
    /* 0x18 */ void *pad18[(0x7C - 0x18) / 4];
    /* 0x7C */ void (*unk7C)(s32);
    /* 0x80 */ void *unk80;
    /* 0x84 */ void (*unk84)(s32);
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
extern u16 D_00359A98[];
extern void func_001536B0(void);
extern void func_001589C8(void);
extern s32 func_00145618(void);
extern void func_001CF738(s32);
extern s32 func_2074968(void);
extern void func_0031AF58(void);
extern void func_00313750(void);
extern void func_00314DF8(s32, s32);
extern void func_0031B770(void);
extern void func_00315440(s32);
extern void func_0031BDC0(const char *, void *, s32);
extern void func_00175380(s32);
extern void func_00317560(s32);
extern void func_00172330(void);
extern void func_00217230(void);
extern void func_0031AE68(void);
extern void func_001533F0(void);
extern void func_00317950(const char *);
extern s32 func_0031C720(void);
extern void func_00317988(s32);
extern void func_002356F8(void);

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

FfxConfig *func_001306A0(void) {
    return (FfxConfig *)D_004AB7C0;
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
    func_001306A0()->unkC = v;
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

    if (func_001306A0()->unkC) {
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

void func_001321D0(void) {
    TkStatus *p;
    s32 i;

    func_0033ED50("TK:SAVE WORK INIT\n");
    p = func_00130A40();
    p->unk0[0] = 0;
    p->unkC = 0;
    p->unk0[2] = 0xFFFF;
    p->unk0[1] = 0;
    p->unkD = 0;
    p->unk0[3] = 0xFFFF;
    p->unkE = 0;
    p->unk10 = ((p->unk10 & 0x7FFFFFF) | 0x2000000) & ~0x4000000;
    p->unk14 = 0;
    p->unk18 = 0;
    p->unk1C = 0;
    p->unkD2 = 0;
    p->unkD3 = 0;
    p->unkD4 = 0;
    p->unkD6 = 0;
    p->unkD7 = 0;
    for (i = 55; i >= 0; i--) {
        p->unk10C[i] = 0;
    }
    for (i = 7; i >= 0; i--) {
        p->unk2C[i] = 0;
    }
    for (i = 19; i >= 0; i--) {
        p->unk4C[i] = 0;
    }
    for (i = 0; i < 8; i++) {
        p->unkAC[i] = i;
    }
    p->unkD0 = 2;
    p->unkEC = 0;
    p->unk2A = 0;
    p->unkB8 = 0;
    p->unkBA = 0;
    p->unkB4 = 0;
    p->unkB6 = 0;
    p->unk20 = 0;
    p->unk21 = 0xFF;
    p->unk22 = 0xFF;
    p->unk24 = 0;
    p->unk28 = 0;
    p->unk29 = 0;
    p->unk2B = 0;
    p->unkE4 = 0;
    p->unkE8 = 0;
    p->unkEA = 0;
    p->unk23 = 0xFF;
    func_001536B0();
    func_001589C8();
    if (func_00145618()) {
        func_0033ED50("Tk:Asia(change to English)\n");
        func_001CF738(1);
    }
}

u16 func_00132398(s32 x) {
    return D_00359A98[x / 64];
}

u16 func_001323C8(s32 x) {
    return D_00359A98[(0x1000 - x) / 64];
}

void func_00132400(void) {
    u16 *p = D_00359A98;
    s32 v = 0x1000;
    s32 i;
    s32 d = 10;

    p += 64;
    *p = v;
    for (i = 0; i < 64; i++) {
        *--p = v;
        v = v * 9 / d;
    }
    p[-1] = 0;
}

void func_00132458(void) {
    func_0033ED50("TK:Load Vibrate\n");
    func_00131628(0x18, 8, D_004AB800);
}

void func_00132488(void) {
    func_00132458();
}

void func_00132490(void) {
    FfxConfig *c;
    FfxConfig *w;
    FfxConfig *g;
    TkFileIf *f;
    s32 i;
    s32 r;

    func_00130FB8(0x20);
    func_0033ED50("TK:TK INIT\n");
    func_0033ED50("TK:TK INIT START\n");
    func_00131A68();
    func_0033ED50("TK:InitWork Done\n");
    if (func_0031C5E8()) {
        r = func_2074968();
        func_0033ED50("TK:TkDeci2:Init result%d\n", r);
        func_0031AF58();
    }
    func_00313750();
    func_001313B8();
    func_00314DF8(0, 0);
    func_00314DF8(1, 0);
    func_0033ED50("TK:Read Controler Done\n");
    func_0031B770();
    func_00315440(2);
    func_0033EBE0(func_001306A0(), 0, 0x40);
    w = func_001306A0();
    w->unkE = D_00473A58;
    w->unkF = 1;
    w->unk10 = 1;
    for (i = 0; i < 8; i++) {
        w->unk11[i] = 0;
    }
    w->unk11[0] |= 2;
    w->unk11[2] |= 0x20;
    w->unk11[6] |= 2;
    w->unk11[3] |= 0xA;
    if (!func_00130650()) {
        func_0033ED50("ReadConfig Start\n");
        func_0031BDC0("FFXCONFIG", func_001306A0(), 0x40);
        func_0033ED50("ReadConfig Done\n");
    }
    c = func_001306A0();
    func_00175380(c->unk8);
    func_0033ED50("======================================================\n");
    func_0033ED50("\tFFXCONF:printf        :%d\n", c->unk8);
    func_0033ED50("\tFFXCONF:cd read       :%d\n", c->unkA);
    func_0033ED50("\tFFXCONF:movie read    :%d\n", c->unkF);
    func_0033ED50("\tFFXCONF:DVD printf cut:%d\n", c->unkB);
    func_0033ED50("\tFFXCONF:Menu Debug    :%d\n", c->unk9);
    func_0033ED50("\tFFXCONF:yi Assert     :%d\n", c->unkC);
    func_0033ED50("\tFFXCONF:MusicMute     :%d\n", c->unkD);
    func_0033ED50("\tFFXCONF:BootType      :%d\n", c->unkE);
    func_0033ED50("\tFFXCONF:ThreadMode    :%d\n", c->unk10);
    func_0033ED50("======================================================\n");
    func_00317560(c->unkD);
    D_00473A58 = c->unkE;
    func_00131AF8();
    func_00172330();
    f = func_00172340();
    g = func_001306A0();
    f->unk7C(g->unkA);
    f->unk84(g->unkF);
    func_00131938("MAP INFO");
    func_00131890();
    func_00131938("TO INIT");
    func_0033ED50("TK:TO Init Start\n");
    func_00217230();
    func_0033ED50("TK:TO Init Done\n");
    func_001318C0();
    func_0033ED50("TK:TO Read Init File\n");
    if (func_0031C5E8()) {
        func_0033ED50("TK:Enable Debug Font(S-JIS)\n");
        func_0031AE68();
        func_0033ED50("TK:Enable Debug Font(S-JIS) Done.\n");
    }
    func_00131938("ATEL INIT");
    func_0033ED50("TK:ATEL Init Total\n");
    func_001533F0();
    func_0033ED50("TK:ATEL Init Done.\n");
    func_00131938("EVJMP");
    func_00132400();
    r = func_0031C688();
    switch (r) {
        case 0:
            func_00317950("/ffx2/proj/sound");
            break;
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
            func_00317950("/ffx2/proj/sound/us");
            break;
    }
    switch (func_0031C720()) {
        case 0:
            func_00317988(0);
            break;
        case 1:
            func_00317988(1);
            break;
    }
    func_00131938("INIT SOUND");
    func_00132048();
    func_00131938("INIT VOICE");
    func_00131A20();
    func_00131938("HDD");
    func_001320F8();
    func_00131938("VIBRATE");
    func_00132488();
    func_00131938("ABMAP");
    func_00131938("MENU ICON");
    func_002356F8();
    func_001305D0();
    func_0033ED50("TK:Now Video:%d\n", func_0031C720());
    func_00131938("TK INIT DONE");
}

/* Build timestamp, originally __DATE__ "  " __TIME__ (spelled out so the
 * host preprocessor doesn't substitute today's date). */
const char *func_00132908(void) {
    return "Aug 29 2003  20:13:32";
}
