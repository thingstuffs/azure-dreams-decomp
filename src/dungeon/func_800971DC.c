#include "common.h"

typedef struct Ent {
    u8 pad0[3];        /* 0x00 */
    u8 unk3;           /* 0x03 */
    u8 pad4[0xF];      /* 0x04 */
    u8 unk13;          /* 0x13 */
    s32 flags14;       /* 0x14 */
    u8 pad18[4];       /* 0x18 */
    u32 flags1c;       /* 0x1C */
    u16 unk20;         /* 0x20 */
    u8 pad22[4];       /* 0x22 */
    u8 unk26;          /* 0x26 */
    u8 pad27[3];       /* 0x27 */
    u16 unk2a;         /* 0x2A */
    u8 pad2c[0x1A];    /* 0x2C */
    u16 unk46;         /* 0x46 */
    u8 pad48[8];       /* 0x48 */
    u8 *unk50;         /* 0x50 */
    u8 pad54[0xC];     /* 0x54 */
    struct Ent *unk60; /* 0x60 */
    u8 pad64[6];       /* 0x64 */
    u16 unk6a;         /* 0x6A */
    u8 pad6c[4];       /* 0x6C */
    u8 unk70;          /* 0x70 */
    u8 pad71[0x13];    /* 0x71 */
    u8 unk84;          /* 0x84 */
    u8 pad85[3];       /* 0x85 */
    s16 unk88;         /* 0x88 */
} Ent;

typedef struct {
    u8 pad0[0x24];
    u8 unk24;          /* 0x24 */
    u8 unk25;          /* 0x25 */
} Pos;

extern s16 D_8006CCD8[];
extern s16 D_8006CCE8[];
extern u16 D_800DCEAC[];
extern u16 D_800DCEBC[];
extern u8 *D_800E3D7C;

extern s32 func_800A6D30();
extern void func_800C78A0(void *, s32, s32, s32, s32, s32);
extern s32 func_8009A540(s32, s32, s32, s32);
extern Ent *func_8009B25C(Ent *, s32, s32, s32);
extern s32 func_800981F8(Ent *);
extern void func_8003E188(s32, s32);

Ent *func_8009C93C(Ent *a, Pos *b, u32 coordArg, s32 mult, Ent *ent2) {
    register s32 zero ASM_REG("$0");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    u32 coord;
    s32 savedMult;
    s32 off;
    s32 shifted;
    s32 value;
    s32 step;
    u8 *base;
    u16 *tableA;

#ifdef NON_MATCHING
    zero = 0;
#else
#endif
    coord = coordArg + zero;
    savedMult = mult + zero;
    if (ent2 == 0) {
        if (a->flags1c & 0x400) {
            register s32 f ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

            base = (u8 *)a - 0x20;
            f = a->flags14;

            if (f >= 0) {
                u32 nc;

                f |= 0x80000000;
                a->flags14 = f;
                nc = coordArg + ((func_800A6D30(base, coord, coordArg, mult) & 7) << 9);
                coord = nc + zero;
                a->unk2a = nc;
            }
        }
    }
    base = (u8 *)a - 0x20;
    shifted = coord >> 8;
    tableA = D_800DCEAC;
    off = shifted & 0xE;
       /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    func_800C78A0(base,
                  (b->unk24 << 6) + ((s16)*(u16 *)((u8 *)tableA + off) >> 1) + 0x20,
                  (b->unk25 << 6) + ((s16)*(u16 *)((u8 *)D_800DCEBC + off) >> 1) + 0x20,
                  a->unk88, 8, 0x300);
    a->unk60 = ent2;
    a->flags14 &= ~0x4000000;
    if (ent2 == 0) {
        if ((func_8009A540((a->unk2a >> 9) & 7, b->unk24, b->unk25,
                           (s16)(*(u16 *)&a->unk88 - 0x20)) << 16) != 0) {
            ent2 = func_8009B25C(a,
                                 (u16)(b->unk24 + *(u16 *)((u8 *)D_8006CCD8 + off) * savedMult),
                                 (u16)(b->unk25 + *(u16 *)((u8 *)D_8006CCE8 + off) * savedMult),
                                 a->unk88);
            a->unk60 = ent2;
            if (ent2 != 0) {
                goto created;
            }
        }
        return 0;
    }
created:
    ent2->unk6a = a->unk2a;
    if (ent2->unk13 != 0) {
        if ((ent2->flags1c & 0x238) != 0) {
            goto adjusted;
        }
        if ((ent2->unk46 & 0x8000) != 0) {
            goto adjusted;
        }
        ent2->unk2a = a->unk2a + 0x800;
    }
adjusted:
    a->flags14 |= 0x4000000;
    ent2->flags14 = (ent2->flags14 | 0x20000) & ~0x1000000;

    {
        register s32 dance ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

        dance = a->unk84;
        step = dance;
        {
            register s32 r ASM_REG("$3") = func_800A6D30() & 0xFFFF;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

            ASM_KEEP(dance);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
            dance = step;
            if (a->unk3 != 0) {
                r %= a->unk3;
                ASM_USE_NV(r);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                dance = step + r * 4;
            }
        }
        value = dance;
    }
    if (ent2->unk13 == 0) {
        u8 *p = ent2->unk50;

        if (p != 0 && *p == 2) {
            value -= (s16)value >> 2;
        }
    }
    if ((ent2->flags1c & 0x238) == 0 && (s16)value < 0x80) {
        return ent2;
    }
    value = func_800A6D30();
    {
        register Ent *callArg ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */

        callArg = a;
        step = value & 1;
        {
            s32 t2 = value & 2;

            step += (t2 != 0);
        }
        step += (a->unk26 + (s16)func_800981F8(callArg)) * 2;
    }
    a->unk20 = step;
    if (a->flags1c & 0x1000) {
        value = a->unk3 >> 1;
    } else {
        value = a->unk3 >> 6;
    }
    if ((s16)value >= (s32)(func_800A6D30() & 0x7F)) {
        a->flags1c |= 0x1000000;
    } else {
        a->flags1c &= ~0x1000000;
    }
    if ((ent2->flags1c & 0x238) != 0) {
        register s32 m ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        u8 d;

        m = func_800A6D30() & 0xFFFF;
        d = ent2->unk3;

        if (d != 0) {
            s32 dd = d + zero; /* move v0,v1 */

            value = (m % dd) + zero; /* mfhi; move s1 */
            ASM_USE_NV(dd);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        } else {
            value = 0;
        }
        {
            register s32 sum ASM_REG("$2") = ent2->unk70;   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

            sum = value + sum;
            if (((s16)sum >> 7) > 0) {
                return ent2;
            }
        }
    }
    a->flags14 &= ~0x4000000;
    ent2->flags14 &= ~0x20000;
    if ((u8 *)a == D_800E3D7C) {
        func_8003E188(ent2->unk13, 0);
    }
    return ent2;
}
