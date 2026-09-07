#include "common.h"

typedef struct S_80173A3C_0 {
    u8 pad_00[0x96];
    union { s16 s; u16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
} S_80173A3C_0;   /* arg0 in func_80173A3C */

typedef struct S_80173A3C_1 {
    u8 pad_00[0xC];
    union { struct { u32 v; } at00; struct { u8 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; struct { u8 pad[0x2]; u8 v; } at02; } unk_0C;   /* overlapping accesses */
    s16 unk_10;
    u16 unk_12;
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
    u8 pad_20[0x4];
    u8 unk_24;
    u8 unk_25;
} S_80173A3C_1;   /* arg2 in func_80173A3C */

typedef struct S_80173A3C_2 {
    u8 pad_00[0x14];
    u32 unk_14;
    u8 pad_18[0x4];
    u32 unk_1C;
    u8 pad_20[0x29];
    u8 unk_49;
    u8 pad_4A[0x1];
    u8 unk_4B;
    u8 pad_4C[0x3C];
    s16 unk_88;
} S_80173A3C_2;   /* arg3 in func_80173A3C */

typedef struct S_80173A3C_3 {
    u8 pad_00[0x10];
    union { void * p; u32 i; } unk_10;   /* accessed as both */
} S_80173A3C_3;   /* global in func_80173A3C */

typedef struct S_80173A3C_4 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
} S_80173A3C_4;   /* arg1 in func_80173A3C */



extern void func_800A56E0(s32);
extern void func_800A2FE0(void *);
extern void func_800A32A4(void *);
extern void func_800B8228(s32, s32, s32, void *);
extern s32 func_80042900(void *, s32);
extern void func_8009A3D0(s32, s32, s32);
extern void func_8009A028(void *);
extern void func_800ACF88(void *);

extern s32 D_800814A0;
extern s32 D_80083460;
extern s16 D_8008346A;

void func_80173A3C(void *arg0, void *arg1, void *arg2, void *arg3)
{
    u8 state;
    u16 timer;

    state = ((S_80173A3C_0 *)arg0)->unk_9B;
    if (state == 0) {
        goto state_zero;
    }
    if (state == 1) {
        goto update;
    }
    return;

state_zero:
    if (D_8008346A != 0) {
        return;
    }

    ((S_80173A3C_0 *)arg0)->unk_9B = 1;
    ((S_80173A3C_1 *)arg2)->unk_10 = 0x20;
    ((S_80173A3C_1 *)arg2)->unk_12 -= 0x80;
    ((S_80173A3C_1 *)arg2)->unk_14 |= 0xC;
    ((S_80173A3C_2 *)arg3)->unk_1C |= 0x10000000;
    func_800A56E0(0x805);
    ((S_80173A3C_1 *)arg2)->unk_0C.at00.v = 0x00808080;
    ((S_80173A3C_0 *)arg0)->unk_96.s = 0xC;

update:
    ((S_80173A3C_1 *)arg2)->unk_0C.at00u.v -= ((S_80173A3C_1 *)arg2)->unk_0C.at00u.v / ((S_80173A3C_0 *)arg0)->unk_96.s;
    ((S_80173A3C_1 *)arg2)->unk_0C.at01.v -= ((S_80173A3C_1 *)arg2)->unk_0C.at01.v / ((S_80173A3C_0 *)arg0)->unk_96.s;
    ((S_80173A3C_1 *)arg2)->unk_0C.at02.v -= ((S_80173A3C_1 *)arg2)->unk_0C.at02.v / ((S_80173A3C_0 *)arg0)->unk_96.s;

    ((S_80173A3C_1 *)arg2)->unk_1C >>= 2;
    ((S_80173A3C_1 *)arg2)->unk_1E >>= 1;
    ((S_80173A3C_1 *)arg2)->unk_1C *= 3;
    ((S_80173A3C_1 *)arg2)->unk_1E *= 3;

    timer = ((S_80173A3C_0 *)arg0)->unk_96.u - 1;
    ((S_80173A3C_0 *)arg0)->unk_96.u = timer;
    if (((s32)timer << 16) > 0) {
        if ((((S_80173A3C_1 *)arg2)->unk_14 & 0x8000) == 0) {
            return;
        }
    }

    if ((((S_80173A3C_2 *)arg3)->unk_14 & 0x20000000) == 0) {
        u8 *global = (u8 *)&D_80083460;
        if (((S_80173A3C_3 *)global)->unk_10.p == (u8 *)arg3 - 0x20) {
            ((S_80173A3C_3 *)global)->unk_10.i &= 0x7FFFFFFF;
        }
    }

    if ((((S_80173A3C_2 *)arg3)->unk_14 & 0x4000) == 0) {
        func_800A2FE0(arg3);
        func_800A32A4(arg3);
        if (((S_80173A3C_2 *)arg3)->unk_49 != 0 &&
            (((S_80173A3C_2 *)arg3)->unk_4B & 0x20) == 0) {
            func_800B8228(((S_80173A3C_4 *)arg1)->unk_02, ((S_80173A3C_4 *)arg1)->unk_06,
                          ((S_80173A3C_2 *)arg3)->unk_88, (u8 *)arg3 + 0x48);
        }
        if ((func_80042900(arg3, 0x1B) << 16) == 0) {
            s32 flags = ((S_80173A3C_2 *)arg3)->unk_1C;
            s32 color0 = ((S_80173A3C_1 *)arg2)->unk_24;
            s32 color1 = ((S_80173A3C_1 *)arg2)->unk_25;
            s32 effect = 0x3000;
            if (flags & 0x2000) {
                effect = 0x300;
            }
            func_8009A3D0(color0, color1, effect);
        }
        func_8009A028(arg3);
        (*(u16 *)((u8 *)arg3 + -2)) |= 0x8000;
        D_800814A0 |= 0x8000;
        return;
    }

    if ((((S_80173A3C_2 *)arg3)->unk_14 & 0x20000000) == 0) {
        func_800ACF88(arg3);
    }
    func_800A2FE0(arg3);
    func_800A32A4(arg3);
    if ((func_80042900(arg3, 0x1B) << 16) == 0) {
        s32 flags = ((S_80173A3C_2 *)arg3)->unk_1C;
        s32 color0 = ((S_80173A3C_1 *)arg2)->unk_24;
        s32 color1 = ((S_80173A3C_1 *)arg2)->unk_25;
        s32 effect = 0x3000;
        if (flags & 0x2000) {
            effect = 0x300;
        }
        func_8009A3D0(color0, color1, effect);
    }
    func_8009A028(arg3);
    (*(u16 *)((u8 *)arg3 + -2)) |= 0x8000;
    D_800814A0 |= 0x8000;
    func_800A56E0(0x609);
}
