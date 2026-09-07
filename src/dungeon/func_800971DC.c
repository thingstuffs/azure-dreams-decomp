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

extern s32 func_800A6D30(void);
extern void func_800C78A0(void *, s32, s32, s32, s32, s32);
extern s32 func_8009A540(s32, s32, s32, s32);
extern Ent *func_8009B25C(Ent *, s32, s32, s32);
extern s32 func_800981F8(Ent *);
extern void func_8003E188(s32, s32);
extern void func_8009CD34(void) __attribute__((noreturn));
extern void func_8009CC54(void) __attribute__((noreturn));
extern void func_8009CC8C(void) __attribute__((noreturn));
extern void func_8009CCD4(void) __attribute__((noreturn));

Ent *func_8009C93C(Ent *a, Pos *b, u32 coordArg, s32 mult, Ent *ent2) {
    s32 zero;
    u32 coord;
    s32 off;
    s32 value;
    s32 saved;
    s32 step;
    u8 *base;

    zero = 0;
    coord = coordArg + zero;
    if (ent2 == 0) {
        if (a->flags1c & 0x400) {
            s32 f;

            f = a->flags14;

            if (f >= 0) {
                u32 nc;

                f |= 0x80000000;
                a->flags14 = f;
                nc = coordArg + ((func_800A6D30() & 7) << 9);
                coord = nc + zero;
                a->unk2a = nc;
            }
        }
    }
    base = (u8 *)a - 0x20;
    off = (coord >> 8) & 0xE;
    func_800C78A0(base,
                  (b->unk24 << 6) + ((s16)*(u16 *)((u8 *)D_800DCEAC + off) >> 1) + 0x20,
                  (b->unk25 << 6) + ((s16)*(u16 *)((u8 *)D_800DCEBC + off) >> 1) + 0x20,
                  a->unk88, 8, 0x300);
    a->unk60 = ent2;
    a->flags14 &= ~0x4000000;
    if (ent2 == 0) {
        if ((func_8009A540((a->unk2a >> 9) & 7, b->unk24, b->unk25,
                           (s16)(*(u16 *)&a->unk88 - 0x20)) << 16) != 0) {
            ent2 = func_8009B25C(a,
                                 (u16)(b->unk24 + *(u16 *)((u8 *)D_8006CCD8 + off) * mult),
                                 (u16)(b->unk25 + *(u16 *)((u8 *)D_8006CCE8 + off) * mult),
                                 a->unk88);
            a->unk60 = ent2;
            if (ent2 != 0) {
                goto created;
            }
        }
        {
            s32 result;

            result = 0;
            func_8009CD34();
        }
    }
created:
    ent2->unk6a = a->unk2a;
    if (ent2->unk13 != 0) {
        if ((ent2->flags1c & 0x238) == 0 && (ent2->unk46 & 0x8000) == 0) {
            ent2->unk2a = a->unk2a + 0x800;
        }
    }
    a->flags14 |= 0x4000000;
    ent2->flags14 = (ent2->flags14 | 0x20000) & ~0x1000000;

    value = a->unk84;
    saved = value;
    {
        s32 r = func_800A6D30() & 0xFFFF;

        value = saved;
        if (a->unk3 != 0) {
            value = saved + (r % a->unk3) * 4;
        }
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
    step = value & 1;
    {
        s32 t2 = value & 2;

        step += (t2 != 0);
    }
    step += (a->unk26 + (s16)func_800981F8(a)) * 2;
    a->unk20 = step;
    if (a->flags1c & 0x1000) {
        value = a->unk3 >> 1;
        func_8009CC54();
    }
    value = a->unk3 >> 6;
    if ((s16)value >= (s32)(func_800A6D30() & 0x7F)) {
        s32 result2;

        result2 = a->flags1c;
        result2 |= 0x1000000;
        func_8009CC8C();
    }
    a->flags1c &= ~0x1000000;
    if ((ent2->flags1c & 0x238) != 0) {
        s32 m;
        u8 d;

        m = func_800A6D30() & 0xFFFF;
        d = ent2->unk3;

        if (d != 0) {
            s32 dd = d + zero; /* move v0,v1 */

            value = (m % dd) + zero; /* mfhi; move s1 */
            func_8009CCD4();
        } else {
            value = 0;
        }
        if (((s16)(value + ent2->unk70) >> 7) > 0) {
            return ent2;
        }
    }
    a->flags14 &= ~0x4000000;
    ent2->flags14 &= ~0x20000;
    if ((u8 *)a == D_800E3D7C) {
        func_8003E188(ent2->unk13, 0);
    }
    return ent2;
}
