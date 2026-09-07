#include "common.h"

typedef struct S_8016CBAC_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    s32 unk_90;
    u8 pad_94[0x2];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x2];
    union { s16 s; u16 u; } unk_9E;   /* accessed as both */
    u8 pad_A0[0x4];
    s32 unk_A4;
} S_8016CBAC_0;   /* arg0 in func_8016CBAC */

typedef struct S_8016CBAC_1 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    u8 * unk_2C;
} S_8016CBAC_1;   /* arg2 in func_8016CBAC */

typedef struct S_8016CBAC_2 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
} S_8016CBAC_2;   /* arg3 in func_8016CBAC */

typedef struct S_8016CBAC_3 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x4];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_8016CBAC_3;   /* arg1 in func_8016CBAC */

typedef struct S_8016CBAC_4 {
    u8 pad_00[0x8];
    union { s16 s; u16 u; } unk_08;   /* accessed as both */
} S_8016CBAC_4;   /* global_base in func_8016CBAC */

typedef struct S_8016CBAC_5 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_8016CBAC_5;   /* map_base in func_8016CBAC */



extern void func_80047784(void *, s32, s32);
extern s32 func_800644B8(s32);
extern s16 func_800A0818(s32, s32, s32, s32, void *);
extern void func_800A2B04(void *, s32, s32);
extern void func_800A4ACC(void *);
extern void func_800A9A04(void *);
extern void func_800AD594(void *, s32);
extern s32 func_800AD9B4(void *, void *);

extern u8 D_80082E80[];
extern s16 D_80083228;
extern s32 D_80083460;
extern s32 D_8016B728;
extern u8 D_8016EDEC[];
extern u8 D_8016EE0C[];
extern u8 D_8016EE14[];

void func_8016CBAC(void *arg0, void *arg1, void *arg2, void *arg3)
{
    s32 state;
    s32 remaining;
    s32 tile_x;
    s32 x;
    s32 sum;
    s32 velocity;
    s32 y;
    s32 counter;
    s32 timer;
    s32 flags;
    s32 sp18;
    u8 *global_base;
    u8 *map_base;

    state = ((S_8016CBAC_0 *)arg0)->unk_9B;
    if (state == 1) {
        goto state_one;
    }
    if (state < 2) {
        if (state == 0) {
            goto state_zero;
        }
        goto decrement_timer;
    }
    if (state == 2) {
        goto state_two;
    }
    if (state == 3) {
        goto state_three;
    }
    goto decrement_timer;

state_zero:
    if (!(((S_8016CBAC_1 *)arg2)->unk_14 & 0x6000)) {
        goto decrement_timer;
    }
    (*(u8 * *)((u8 *)arg2 + 0x2C)) = D_8016EE0C;
    func_80047784(
        arg2,
        D_8016EE0C[((D_80083228 + ((S_8016CBAC_2 *)arg3)->unk_2A + 0x100) >> 9) & 7],
        0);
    ((S_8016CBAC_0 *)arg0)->unk_98 |= 8;
    ((S_8016CBAC_2 *)arg3)->unk_1C &= 0xF7FFFFFF;
    ((S_8016CBAC_0 *)arg0)->unk_9E.s = 5;
    ((S_8016CBAC_0 *)arg0)->unk_A4 = 0;
    ((S_8016CBAC_0 *)arg0)->unk_9B++;

state_one:
    remaining = ((S_8016CBAC_0 *)arg0)->unk_9E.s;
    ((S_8016CBAC_0 *)arg0)->unk_90 -= ((S_8016CBAC_0 *)arg0)->unk_A4;
    if (remaining != 0) {
        tile_x = ((S_8016CBAC_1 *)arg2)->unk_24;
        x = ((S_8016CBAC_3 *)arg1)->unk_02;
        tile_x <<= 6;
        x -= 0x20;

        ((S_8016CBAC_3 *)arg1)->unk_0C = ((tile_x - x) << 16) / remaining;

        y = ((S_8016CBAC_3 *)arg1)->unk_06;
        y -= 0x20;
        ((S_8016CBAC_3 *)arg1)->unk_10 =
            (((((S_8016CBAC_1 *)arg2)->unk_25 << 6) - y) << 16) /
            ((S_8016CBAC_0 *)arg0)->unk_9E.s;

        ((S_8016CBAC_0 *)arg0)->unk_A4 =
            (-func_800644B8(((S_8016CBAC_0 *)arg0)->unk_9E.s * 0x199)) << 10;
    }

    sum = ((S_8016CBAC_0 *)arg0)->unk_90;
    velocity = ((S_8016CBAC_0 *)arg0)->unk_A4;
    counter = ((S_8016CBAC_0 *)arg0)->unk_9E.u;
    sum += velocity;
    counter -= 1;
    ((S_8016CBAC_0 *)arg0)->unk_9E.u = counter;
    ((S_8016CBAC_0 *)arg0)->unk_90 = sum;
    if ((counter << 16) >= 0) {
        goto state_two;
    }

    ((S_8016CBAC_0 *)arg0)->unk_90 = 0;
    ((S_8016CBAC_0 *)arg0)->unk_98 &= 0xFFF7;
    ((S_8016CBAC_2 *)arg3)->unk_1C |= 0x08000000;
    ((S_8016CBAC_0 *)arg0)->unk_9B++;

state_two:
    if (((S_8016CBAC_2 *)arg3)->unk_1C & 0x08000000) {
        ((S_8016CBAC_0 *)arg0)->unk_98 &= 0xFFF7;
        ((S_8016CBAC_3 *)arg1)->unk_14 = 0;
        ((S_8016CBAC_3 *)arg1)->unk_10 = 0;
        ((S_8016CBAC_3 *)arg1)->unk_0C = 0;
        func_800A2B04(arg1, ((S_8016CBAC_1 *)arg2)->unk_24, ((S_8016CBAC_1 *)arg2)->unk_25);
        (*(u8 * *)((u8 *)arg2 + 0x2C)) = D_8016EE14;
        func_80047784(
            arg2,
            D_8016EE14[((D_80083228 + ((S_8016CBAC_2 *)arg3)->unk_2A + 0x100) >> 9) & 7],
            0);
        ((S_8016CBAC_0 *)arg0)->unk_9B++;
    }
    goto decrement_timer;

state_three:
    if (((S_8016CBAC_1 *)arg2)->unk_2C == D_8016EDEC) {
        goto decrement_timer;
    }
    (*(u8 * *)((u8 *)arg2 + 0x2C)) = D_8016EDEC;
    func_80047784(
        arg2,
        D_8016EDEC[((D_80083228 + ((S_8016CBAC_2 *)arg3)->unk_2A + 0x100) >> 9) & 7],
        0);

decrement_timer:
    timer = ((S_8016CBAC_0 *)arg0)->unk_96 - 1;
    ((S_8016CBAC_0 *)arg0)->unk_96 = timer;
    if ((timer << 16) > 0) {
        return;
    }

    ((S_8016CBAC_3 *)arg1)->unk_14 = 0;
    ((S_8016CBAC_3 *)arg1)->unk_10 = 0;
    ((S_8016CBAC_3 *)arg1)->unk_0C = 0;
    func_800A2B04(arg1, ((S_8016CBAC_1 *)arg2)->unk_24, ((S_8016CBAC_1 *)arg2)->unk_25);
    func_800AD594(arg3, 4);
    func_800A4ACC(arg3);

    global_base = (u8 *)&D_80083460;
    if (((S_8016CBAC_4 *)global_base)->unk_08.s != 0) {
        ((S_8016CBAC_4 *)global_base)->unk_08.u--;
    }

    flags = ((S_8016CBAC_2 *)arg3)->unk_1C;
    if (flags & 0x2000) {
        if (((S_8016CBAC_2 *)arg3)->unk_46 & 0x8000) {
            ((S_8016CBAC_2 *)arg3)->unk_46 &= 0x7FFF;
        }
        goto collision_check;
    }
    if (flags & 0x410) {
        goto collision_check;
    }
    if (!(flags & 0x20000)) {
        goto collision_check;
    }
    map_base = D_80082E80;
    ((S_8016CBAC_2 *)arg3)->unk_2A = func_800A0818(
        ((S_8016CBAC_1 *)arg2)->unk_24,
        ((S_8016CBAC_1 *)arg2)->unk_25,
        ((S_8016CBAC_5 *)map_base)->unk_24,
        ((S_8016CBAC_5 *)map_base)->unk_25,
        &sp18);

collision_check:
    if ((func_800AD9B4(arg2, arg3) << 16) > 0) {
        ((S_8016CBAC_0 *)arg0)->unk_8C = &D_8016B728;
        func_800A9A04(arg3);
    }
}
