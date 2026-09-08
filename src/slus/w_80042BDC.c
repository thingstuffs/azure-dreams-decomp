#include "common.h"

/* ------------------------------------------------------------------ *
 * func_80042BDC: a big switch(sel) dispatcher over an entity object.
 * Most handlers clear a bit in the entity's 0x1C flag word and, if bit
 * 0x4000 of the 0x14 flag word is set, emit a debug string via the
 * func_800990FC / func_80099734 / func_80099194 / func_80099290 /
 * func_800A5720 tail (cross-jumped into one shared block).  Case 10 is
 * the large "spawn a new child object" handler.  All paths converge on
 * func_80041E70(ent).
 * ------------------------------------------------------------------ */

typedef struct S_80042BDC {
    /* 0x00 */ u8   pad00[0x13];
    /* 0x13 */ u8   x13;
    /* 0x14 */ u32  x14;
    /* 0x18 */ u8   pad18[0x1C - 0x18];
    /* 0x1C */ u32  x1C;
    /* 0x20 */ u8   pad20[0x25 - 0x20];
    /* 0x25 */ u8   x25;
    /* 0x26 */ u8   pad26[0x60 - 0x26];
    /* 0x60 */ void *x60;
    /* 0x64 */ u8   pad64[0x71 - 0x64];
    /* 0x71 */ u8   x71;
    /* 0x72 */ u8   pad72[0x88 - 0x72];
    /* 0x88 */ s16  x88;
    /* 0x8A */ u16  x8A;
    /* 0x8C */ u8   pad8C[0x98 - 0x8C];
    /* 0x98 */ u16  x98;
    /* 0x9A */ u8   pad9A[0xA6 - 0x9A];
    /* 0xA6 */ u16  xA6;
    /* 0xA8 */ u8   xA8;
} S_80042BDC;

/* child object at *(ent - 0x14) */
typedef struct S_80042BDC_child {
    /* 0x00 */ u8  pad00[0x12];
    /* 0x12 */ s16 x12;
    /* 0x14 */ u8  pad14[0x24 - 0x14];
    /* 0x24 */ u8  x24;
    /* 0x25 */ u8  x25;
} S_80042BDC_child;

/* global stat/counter block (>8B -> hi/lo) */
typedef struct S_80042BDC_83460 {
    /* 0x00 */ u8  pad00[2];
    /* 0x02 */ u16 x2;
    /* 0x04 */ u8  pad04[0x08 - 0x04];
    /* 0x08 */ u16 x8;
    /* 0x0A */ u16 xA;
    /* 0x0C */ u8  pad0C[0x14 - 0x0C];
} S_80042BDC_83460;

extern S_80042BDC_83460 D_80083460;

extern void *D_800E3DF0[32];
extern int   D_800814A0[4];  /* 16B: <= gcc -G16 -> bare macro; > as -G8 -> $at */
extern u8   *D_800E3D7C[];   /* by-value pointer global; %hi/%lo, [0] = the pointer */

extern char D_800E1D55[];
extern char D_800E1D61[];
extern char D_800E1D80[];
extern char D_800E1D9F[];
extern char D_800E1DCF[];
extern char D_800E1DEE[];
extern char D_800E1E0D[];
extern char D_800E1E32[];
extern char D_800E1E4B[];
extern char D_800E1E6A[];
extern char D_800E1E8C[];
extern char D_800E1EC1[];
extern char D_800E1EF7[];
extern char D_800E1F1C[];
extern char D_800E1F41[];

typedef S_80042BDC *(*Ctor_80042BDC)(int a0, int a1, int a2, int a3);

extern void          *func_800990FC(void);
extern int            func_80099734(S_80042BDC *ent, void *ctx);
extern int            func_80099194(char *str, int arg);
extern int            func_80099290(int arg);
extern void           func_800A5720(void *ctx);
extern void           func_800AA53C(S_80042BDC *ent);
extern void           func_800D5460(void *p, int a1, int a2);
extern void          *func_800A1618(int a0, s16 a1);
extern void           func_8009A3D0(int a0, int a1, int a2);
extern Ctor_80042BDC  func_800A0B94(int a0, void *a1, int a2);
extern void           func_8003F320(void);
extern void           func_8004397C(S_80042BDC *ent);
extern void           func_80042710(S_80042BDC *obj, S_80042BDC *ent);
extern void           func_80042984(S_80042BDC *obj);
extern void           func_800A9A0C(S_80042BDC *obj);
extern int            func_800A1BD0(S_80042BDC *ent);
extern void           func_800AA888(S_80042BDC *obj, int a1, int a2, S_80042BDC *a3);
extern void           func_800AC82C(S_80042BDC *obj, int a1, int a2, S_80042BDC *a3);
extern void           func_800A32A4(S_80042BDC *ent);
extern void           func_8009A028(S_80042BDC *ent);
extern void           func_8009A21C(int a0, int a1, int a2);
extern void           func_800AA36C(S_80042BDC *ent, int a1, S_80042BDC_child *a2, S_80042BDC *a3);
extern void           func_80041E70(S_80042BDC *ent);

extern void *jtbl_8002D67C[];

void func_80042BDC(S_80042BDC *ent, s16 sel) {
    S_80042BDC *s0;
    S_80042BDC_child *s2;
    s32 idx;
    static void *const keepalive[] = {
        &&L_1,  &&L_2,  &&L_3,  &&L_4,  &&L_5,  &&L_6,  &&L_7,  &&L_8,
        &&L_9,  &&L_10, &&L_27, &&L_11, &&L_12, &&L_26, &&L_32, &&L_21,
        &&L_18, &&L_19, &&L_20, &&L_def
    };
    (void)keepalive;

    idx = (s16)(sel - 1);
    if ((u32)idx >= 0x20) {
        goto L_def;
    }
    goto *jtbl_8002D67C[idx];

L_1:
    ent->x1C &= ~0x200;
    if (ent->x14 & 0x4000) { s0 = func_800990FC(); func_80099290(func_80099194(D_800E1D55, func_80099734(ent, s0))); func_800A5720(s0); }
    goto L_def;

L_2:
    ent->x1C &= ~0x400;
    if (ent->x14 & 0x4000) { s0 = func_800990FC(); func_80099290(func_80099194(D_800E1D61, func_80099734(ent, s0))); func_800A5720(s0); }
    goto L_def;

L_3:
    ent->x1C &= ~0x10;
    if (ent->x14 & 0x4000) { s0 = func_800990FC(); func_80099290(func_80099194(D_800E1D80, func_80099734(ent, s0))); func_800A5720(s0); }
    if (ent->x13 != 0) {
        func_800AA53C(ent);
    }
    goto L_def;

L_4:
    ent->x1C &= ~0x20;
    if (ent->x14 & 0x4000) { s0 = func_800990FC(); func_80099290(func_80099194(D_800E1D9F, func_80099734(ent, s0))); func_800A5720(s0); }
    goto L_def;

L_5:
    ent->x1C &= ~0x40;
    if (ent->x14 & 0x4000) { s0 = func_800990FC(); func_80099290(func_80099194(D_800E1DCF, func_80099734(ent, s0))); func_800A5720(s0); }
    goto L_def;

L_6:
    ent->x1C &= ~0x80;
    if (ent->x14 & 0x4000) { s0 = func_800990FC(); func_80099290(func_80099194(D_800E1DEE, func_80099734(ent, s0))); func_800A5720(s0); }
    goto L_def;

L_7:
    if (ent->x14 & 0x4000) { s0 = func_800990FC(); func_80099290(func_80099194(D_800E1E0D, func_80099734(ent, s0))); func_800A5720(s0); }
    goto L_def;

L_8:
    ent->x1C &= ~0x800;
    goto L_def;

L_9:
    ent->x1C &= ~0x1000;
    if (ent->x14 & 0x4000) { s0 = func_800990FC(); func_80099290(func_80099194(D_800E1E32, func_80099734(ent, s0))); func_800A5720(s0); }
    goto L_def;

L_10: {
        s32 a1v;
        int flag;
        int a2v;
        int flag2;
        Ctor_80042BDC ctor;
        u32 flags14;

        if (ent->x13 == 0x2E) goto do_D5460;
        if (ent->x13 != 0) goto check_2E;
    do_D5460:
        func_800D5460((u8 *)ent - 0x20, 0x20A0A0, 0x613);
        if (ent->x13 == 0) goto L_print4B;
    check_2E:
        a1v = 1;
        if (ent->x13 != 0x2E) goto L_print4B;

        s2 = *(S_80042BDC_child **)((u8 *)ent - 0x14);
        flags14 = ent->x14;
        ent->x13 = ent->xA8;
        if (flags14 & 0x4000) {
            a1v = 3;
        }
        ASM_KEEP_NV(a1v);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        {
        S_80042BDC *r = func_800A1618(ent->x13, a1v);
        a2v = 0x3000;
        {
            u32 bit = 0x10000;
            ASM_KEEP(bit);   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
            ent->x1C |= bit;
        }
        s0 = r;
        }
        flag = (ent->x14 >> 14) & 1;
        {
            register int a24 ASM_REG("$2") = s2->x24;   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
            int a25 = s2->x25;
            if (ent->x1C & 0x2000) { a2v = 0x300; }
            func_8009A3D0(a24, a25, a2v);
        }
        func_8004397C(ent);

        ctor = func_800A0B94(ent->x13, s0, 1);
        func_8003F320();
        s0 = ctor(flag, s2->x24, s2->x25, ent->x88);

        s0->x14 = 0;
        s0->x1C = 0;
        flag2 = (ent->x1C >> 19) & 1;
        func_80042710(s0, ent);
        func_80042984(s0);

        if (D_80083460.x2 & 0x1000) {
            if (ent->x71 > (s16)ent->x8A) {
                D_80083460.x8 -= (ent->x71 - ent->x8A);
            }
        }
        func_800A9A0C(s0);
        s0->x1C &= ~0x10000;

        if (ent->x14 & 0x4000) {
            u8 *p;
            u8 *q;
            int i2;
            int r;
            r = func_800A1BD0(ent);
            p = (u8 *)((s16)r * 4 + (u32)D_800E3D7C[0]);
            q = *(u8 **)(p + 0xD0);
            i2 = *(u8 *)(q + 3) & 0x1F;
            D_800E3DF0[i2] = s0;
            *(S_80042BDC **)(p + 0xAC) = s0;
        }

        {
        register int f2 ASM_REG("$2") = flag2;   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
        if (f2) {
            S_80042BDC *p4 = s0;
            u8 *w;
            ASM_KEEP_NV(p4);   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
            w = D_800E3D7C[0];
            *(S_80042BDC **)(w + 0x124) = s0;
            s0->x60 = w;
            s0->x1C |= 0x80000;
            func_800AA888(p4, *(int *)((u8 *)s0 - 0x18), *(int *)((u8 *)s0 - 0x14), s0);
            func_800AC82C(s0, *(int *)((u8 *)s0 - 0x18), *(int *)((u8 *)s0 - 0x14), s0);
        } else {
            if (s0->x25 == 0) {
                D_80083460.xA += 1;
                s0->x1C &= ~0x8;
            }
        }

        }
        ent->x14 |= 0x20000000;
        func_800A32A4(ent);
        func_8009A028(ent);
        *(u16 *)((u8 *)ent - 2) |= 0x8000;
        D_800814A0[0] |= 0x8000;
        ent = s0;

    L_print4B:
        if (ent->x14 & 0x4000) { s0 = func_800990FC(); func_80099290(func_80099194(D_800E1E4B, func_80099734(ent, s0))); func_800A5720(s0); }
        goto L_def;
    }

L_27:
    s2 = *(S_80042BDC_child **)((u8 *)ent - 0x14);
    func_8009A21C(s2->x24, s2->x25, (ent->x1C & 0x2000) ? 0x300 : 0x3000);
    func_800AA36C(ent, *(int *)((u8 *)ent - 0x18), s2, ent);
    goto L_def;

L_11:
    s2 = *(S_80042BDC_child **)((u8 *)ent - 0x14);
    func_8009A3D0(s2->x24, s2->x25, (ent->x1C & 0x2000) ? 0x300 : 0x3000);
    ent->x1C &= ~0x2000;
    func_8009A21C(s2->x24, s2->x25, (ent->x1C & 0x2000) ? 0x300 : 0x3000);
    goto L_def;

L_12:
    if (ent->x14 & 0x4000) { s0 = func_800990FC(); func_80099290(func_80099194(D_800E1E6A, func_80099734(ent, s0))); func_800A5720(s0); }
    s2 = *(S_80042BDC_child **)((u8 *)ent - 0x14);
    func_8009A3D0(s2->x24, s2->x25, (ent->x1C & 0x2000) ? 0x300 : 0x3000);
    ent->x1C |= 0x2000;
    func_8009A21C(s2->x24, s2->x25, (ent->x1C & 0x2000) ? 0x300 : 0x3000);
    goto L_def;

L_26:
    s2 = *(S_80042BDC_child **)((u8 *)ent - 0x14);
    ent->x98 &= 0x7FFF;
    func_8009A3D0(s2->x24, s2->x25, (ent->x1C & 0x2000) ? 0x300 : 0x3000);
    if (ent->x98 & 0x4000) {
        ent->x1C |= 0x2000;
    }
    func_8009A21C(s2->x24, s2->x25, (ent->x1C & 0x2000) ? 0x300 : 0x3000);
    s2->x12 = ent->xA6;
    goto L_def;

L_32:
    if (ent->x14 & 0x4000) { s0 = func_800990FC(); func_80099290(func_80099194(D_800E1E8C, func_80099734(ent, s0))); func_800A5720(s0); }
    goto L_def;

L_21:
    if (ent->x14 & 0x4000) { s0 = func_800990FC(); func_80099290(func_80099194(D_800E1EC1, func_80099734(ent, s0))); func_800A5720(s0); }
    goto L_def;

L_18:
    if (ent->x14 & 0x4000) { s0 = func_800990FC(); func_80099290(func_80099194(D_800E1EF7, func_80099734(ent, s0))); func_800A5720(s0); }
    goto L_def;

L_19:
    if (ent->x14 & 0x4000) { s0 = func_800990FC(); func_80099290(func_80099194(D_800E1F1C, func_80099734(ent, s0))); func_800A5720(s0); }
    goto L_def;

L_20:
    if (ent->x14 & 0x4000) { s0 = func_800990FC(); func_80099290(func_80099194(D_800E1F41, func_80099734(ent, s0))); func_800A5720(s0); }

L_def:
    func_80041E70(ent);
}
