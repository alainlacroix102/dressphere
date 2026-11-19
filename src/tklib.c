#include "common.h"

/* tklib.c (name from the retail __FILE__ strings). Starts after the
 * handwritten VU0 module; 0x1305D0 is a guess for the start, since this
 * code shares the status struct with the POPSTATUS functions. Decompiled so
 * far: 0x1305D0-0x130FE8. */

typedef struct {
    /* 0x00 */ u16 unk0[6];
    /* 0x0C */ u8 unkC;
    /* 0x0D */ u8 unkD;
    /* 0x0E */ u8 padE[0x2A - 0xE];
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

TkStatus *func_00130A40(void);
void func_00130A88(s32 a, s32 b);

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
