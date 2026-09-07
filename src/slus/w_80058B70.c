#include "common.h"

/* S_80058B70: view of the D_80085FA8[] element struct touched here (base passed
 * to func_80058ABC/func_80058B2C/func_800589B8; direct fields f00,f1c,f20,f24). */
typedef struct {
    s32 f00, f04, f08, f0c, f10, f14, f18, f1c, f20, f24, f28, f2c;
    s32 f30, f34, f38, f3c, f40, f44;
    s8 f48; u8 f49; s8 f4a, f4b, f4c, f4d[3];
} S_80058B70;

extern S_80058B70 D_80085FA8[32];
extern s32 D_80085FA4[4];   /* [0] = base pointer to another struct */
extern s32 D_80085FA0[4];
extern s32 D_800737C4[4];
extern s32 D_800737C8[4];
extern s32 D_800737D4[4];
extern s32 D_800869A8[4];
extern s32 D_800869B0[4];
extern s32 D_800869B4[4];
extern s32 D_800869B8[4];

extern s32 func_80058850(s32);
extern s32 func_80058940(s32);
extern u32 func_80058ABC(S_80058B70 *);
extern s32 func_80058B2C(S_80058B70 *);
extern void func_800589B8(S_80058B70 *);

/* Configures the D_80085FA8[0] playback slot depending on the current mode
 * D_800737C8 (see doc). */
s32 func_80058B70(void)
{
    S_80058B70 *p = &D_80085FA8[0];
    s32 s1 = 0;
    s32 i;
    u32 tv0;
    u32 lo;
    u32 q;

    D_800737D4[0] = 0;
    switch (D_800737C8[0]) {
    case 1:
        {
            s32 r = func_80058850(0);
            p->f00 = r;
            if (r == -1) {
                return 0;
            }
        }
        D_80085FA0[0] = func_80058ABC(p);
        D_800869B8[0] = func_80058B2C(p) & 0xFFFF;
        D_800869B4[0] = func_80058B2C(p) & 0xFFFF;
        D_800869A8[0] = func_80058B2C(p) & 0xFFFF;
        if (D_800869B8[0] == 0) {
            s32 r;
            D_800869B0[0] = 0x10000;
            r = func_80058940(0);
            D_800869B0[0] = r;
            p->f1c = r;
        } else {
            i = 0;
            D_800869B0[0] = 0x10000;
            if ((u32)s1 < (u32)D_800869B4[0]) {
                do {
                    s1 = func_80058940(s1);
                    i++;
                    p->f1c = s1;
                } while ((u32)i < (u32)D_800869B4[0]);
            }
            D_800869B0[0] = s1;
        }
        break;
    case 0:
        p->f00 = 8;
        D_800869A8[0] = func_80058B2C(p) & 0xFFFF;
        D_800869B8[0] = 0;
        D_800869B4[0] = 1;
        D_800869B0[0] = 0x10000;
        D_800869B0[0] = func_80058940(0);
        tv0 = func_80058ABC(p) >> 8;
        lo = 0x3938700 / tv0;
        p->f20 = tv0;
        p->f24 = lo;
        p->f20 = lo;
        q = (lo * 100) / 115;
        p->f24 = q;
        if (q >= 0x100) {
            p->f24 = 0xFF;
        }
        switch ((u32)D_800869A8[0]) {
        case 0x18:
        case 0x3C:
            p->f24 = (u32)p->f24 >> 1;
            break;
        case 0x1E:
            p->f24 = (u32)p->f24 >> 2;
            break;
        }
        func_800589B8(p);
        break;
    case 2:
        D_800869B8[0] = 1;
        {
            s8 *base = (s8 *)D_80085FA4[0];
            D_800869A8[0] = *(s32 *)(base + 8);
            D_800869B4[0] = *(s32 *)(base + 0xC);
            D_800869B0[0] = *(s32 *)(base + 4);
        }
        break;
    }
    if ((u32)D_800869A8[0] >= 0x60) {
        D_800737C4[0] = D_800869A8[0];
    } else {
        D_800737C4[0] = 0;
    }
    D_800737C4[0] = D_800869A8[0];
    return 1;
}
