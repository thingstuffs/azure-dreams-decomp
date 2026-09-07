#include "common.h"

typedef struct S_801725D0_0 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    union { u16 s; s16 u; } unk_2A;   /* accessed as both */
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x18];
    void * unk_60;
    u8 pad_64[0x9];
    s8 unk_6D;
    u8 pad_6E[0x1A];
    u16 unk_88;
} S_801725D0_0;   /* arg3 in func_801725D0 */

typedef struct S_801725D0_1 {
    u8 pad_00[0x8C];
    s32 * unk_8C;
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; struct { u8 pad[0x2]; s16 v; } at02u; } unk_90;   /* overlapping accesses */
    u8 pad_94[0x2];
    union { u16 s; s16 u; } unk_96;   /* accessed as both */
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0xA];
    s16 unk_A6;
} S_801725D0_1;   /* arg0 in func_801725D0 */

typedef struct S_801725D0_2 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_801725D0_2;   /* arg2 in func_801725D0 */

typedef struct S_801725D0_3_pre {
    void * unk_00;
    u8 pad_04[0x14];
} S_801725D0_3_pre;   /* the 0x18 bytes before linked in func_801725D0, addressed as linked[-1] */

typedef struct S_801725D0_4 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_801725D0_4;   /* entry in func_801725D0 */

typedef struct S_801725D0_5 {
    u8 pad_00[0xA];
    s16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_801725D0_5;   /* arg1 in func_801725D0 */



extern void func_80047784(void *, s32, s32);
extern void func_8009C12C(void *, void *, s16, s32);
extern void func_800A2B04(void *, u8, u8);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern void func_800AD594(void *, s32);
extern s16 func_800BCB04(s32, s32, s16);

extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern s16 D_80083228;
extern s32 D_8008346C;
extern void *D_800E3DE8;
extern s32 D_80170E5C;
extern u8 D_80173D04[];
extern u8 D_80173D34[];

void func_801725D0(void *arg0, void *arg1, void *arg2, void *arg3)
{
    s32 index;
    s32 x_step;
    s32 y_step;
    s32 timer;
    s32 state;
    s32 delta;

    index = (((S_801725D0_0 *)arg3)->unk_2A.s >> 8) & 0xE;
    x_step = *(s16 *)((u8 *)&D_8006CCD8 + index);
    timer = ((S_801725D0_1 *)arg0)->unk_96.s - 1;
    y_step = *(s16 *)((u8 *)&D_8006CCE8 + index);
    state = ((S_801725D0_1 *)arg0)->unk_9B;
    ((S_801725D0_1 *)arg0)->unk_96.s = timer;

    if (state == 2) {
        goto state_2;
    }
    if ((s32)state < 3) {
        if (state == 0) {
            goto state_0;
        }
        if (state == 1) {
            goto state_1;
        }
        goto done;
    }
    if (state == 3) {
        goto state_3;
    }
    if (state == 0xFF) {
        goto state_ff;
    }
    goto done;

state_0:
    if (((S_801725D0_2 *)arg2)->unk_14 & 0x8000) {
        ((S_801725D0_1 *)arg0)->unk_9B = 0xFF;
        ((S_801725D0_2 *)arg2)->unk_14 |= 0x6000;
        func_8009C12C(arg3, arg2, ((S_801725D0_0 *)arg3)->unk_2A.u, 1);
        goto done;
    }

    (*(u8 * *)((u8 *)arg2 + 0x2C)) = D_80173D34;
    func_80047784(
        arg2,
        D_80173D34[((D_80083228 + ((S_801725D0_0 *)arg3)->unk_2A.u + 0x100) >> 9) & 7],
        0);

    if (((S_801725D0_0 *)arg3)->unk_60 != 0) {
        void *linked = ((S_801725D0_0 *)arg3)->unk_60;
        void *entry = ((S_801725D0_3_pre *)linked)[-1].unk_00;
        ((S_801725D0_1 *)arg0)->unk_A6 = ((S_801725D0_4 *)entry)->unk_0A - 0x34;
    } else {
        ((S_801725D0_1 *)arg0)->unk_A6 =
            func_800BCB04(
                ((((S_801725D0_2 *)arg2)->unk_24 + x_step) << 6) & 0xFFC0,
                ((((S_801725D0_2 *)arg2)->unk_25 + y_step) << 6) & 0xFFC0,
                (s16)(((S_801725D0_0 *)arg3)->unk_88 - 0xA0)) - 0x34;
    }
    ((S_801725D0_1 *)arg0)->unk_96.s = 2;
    ((S_801725D0_1 *)arg0)->unk_9B++;
    goto done;

state_1:
    ((S_801725D0_1 *)arg0)->unk_90.at02.v +=
        (((S_801725D0_1 *)arg0)->unk_A6 - ((S_801725D0_5 *)arg1)->unk_0A) / 3;
    if (((S_801725D0_1 *)arg0)->unk_96.u > 0) {
        goto done;
    }

    ((S_801725D0_1 *)arg0)->unk_98 |= 8;
    ((S_801725D0_0 *)arg3)->unk_1C &= 0xF7FFFFFF;
    ((S_801725D0_1 *)arg0)->unk_90.at02u.v = -0x18;
    ((S_801725D0_1 *)arg0)->unk_96.s = 4;
    ((S_801725D0_5 *)arg1)->unk_0C =
        (x_step << 22) / ((S_801725D0_1 *)arg0)->unk_96.u;
    ((S_801725D0_5 *)arg1)->unk_10 = (y_step << 22) / ((S_801725D0_1 *)arg0)->unk_96.u;
    ((S_801725D0_1 *)arg0)->unk_9B++;
    goto done;

state_2:
    ((S_801725D0_1 *)arg0)->unk_90.at00.v +=
        ((((S_801725D0_1 *)arg0)->unk_A6 - ((S_801725D0_5 *)arg1)->unk_0A) / 3) << 16;
    if (((S_801725D0_1 *)arg0)->unk_96.u > 0) {
        goto done;
    }
    ((S_801725D0_5 *)arg1)->unk_10 = 0;
    ((S_801725D0_5 *)arg1)->unk_0C = 0;
    ((S_801725D0_1 *)arg0)->unk_96.s = 10;
    ((S_801725D0_1 *)arg0)->unk_9B++;
    goto done;

state_3:
    delta = ((s32)(timer << 16) >> 4) + 0x2000;
    ((S_801725D0_1 *)arg0)->unk_90.at00.v -= delta;
    if (((S_801725D0_1 *)arg0)->unk_96.u == 6) {
        func_800A56E0(0x808);
    }
    if (((S_801725D0_1 *)arg0)->unk_96.u == 2) {
        func_8009C12C(arg3, arg2, ((S_801725D0_0 *)arg3)->unk_2A.u, 1);
    }
    if (((S_801725D0_1 *)arg0)->unk_96.u > 0) {
        goto done;
    }
    ((S_801725D0_5 *)arg1)->unk_0C = (0 - x_step) << 19;
    ((S_801725D0_5 *)arg1)->unk_10 = (0 - y_step) << 19;
    ((S_801725D0_5 *)arg1)->unk_14 = 0xFFF80000;
    ((S_801725D0_1 *)arg0)->unk_9B = 0xFF;
    goto done;

state_ff:
    ((S_801725D0_5 *)arg1)->unk_14 += 0x18000;
    if (!(((S_801725D0_2 *)arg2)->unk_14 & 0xE000)) {
        goto done;
    }
    ((S_801725D0_5 *)arg1)->unk_14 = 0;
    ((S_801725D0_5 *)arg1)->unk_10 = 0;
    ((S_801725D0_5 *)arg1)->unk_0C = 0;
    ((S_801725D0_1 *)arg0)->unk_98 &= 0xFFF7;
    ((S_801725D0_0 *)arg3)->unk_1C |= 0x08000000;
    ((S_801725D0_1 *)arg0)->unk_90.at00.v = 0;
    (*(u8 * *)((u8 *)arg2 + 0x2C)) = D_80173D04;
    func_80047784(
        arg2,
        D_80173D04[((D_80083228 + ((S_801725D0_0 *)arg3)->unk_2A.u + 0x100) >> 9) & 7],
        0);
    func_800A2B04(arg1, ((S_801725D0_2 *)arg2)->unk_24, ((S_801725D0_2 *)arg2)->unk_25);
    func_800AD594(arg3, 0x100);
    ((S_801725D0_1 *)arg0)->unk_8C = &D_80170E5C;
    D_8008346C = 0;
    func_800A4ACC(arg3);
    if (((S_801725D0_0 *)arg3)->unk_6D == 0) {
        ((S_801725D0_0 *)arg3)->unk_46 &= 0x7FFF;
    } else {
        D_800E3DE8 = (u8 *)arg3 - 0x20;
    }

done:
    return;
}

/* MECHANISM: An s32 timer holds the decremented lhu directly in a0, removing
   the narrowing move and its one-word displacement cascade.  A short-lived
   delta local forces the retail sll/sra/addiu order before the 0x90 load;
   natural argument and step lifetimes produce the exact 0x30/s0-s6 frame. */
