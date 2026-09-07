#include "common.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_D_800E3D7C.h"

typedef struct S_8014EC54_0 {
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
} S_8014EC54_0;   /* arg0 in func_8014EC54 */




typedef struct S_8014EC54_4 {
    u8 pad_00[0x8];
    union { s16 s; u16 u; } unk_08;   /* accessed as both */
} S_8014EC54_4;   /* global_base in func_8014EC54 */

typedef struct S_8014EC54_5 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_8014EC54_5;   /* map_base in func_8014EC54 */



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
extern s32 D_8014D7F4;
extern u8 D_80151988[];
extern u8 D_801519A8[];
extern u8 D_801519B8[];

void func_8014EC54(void *arg0, void *arg1, void *arg2, void *arg3)
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

    state = ((S_8014EC54_0 *)arg0)->unk_9B;
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
    if (!(((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0x6000)) {
        goto decrement_timer;
    }
    (*(u8 * *)((u8 *)arg2 + 0x2C)) = D_801519A8;
    func_80047784(
        arg2,
        D_801519A8[((D_80083228 + ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 + 0x100) >> 9) & 7],
        0);
    ((S_8014EC54_0 *)arg0)->unk_98 |= 8;
    ((Rec_D_800E3D7C *)arg3)->unk_1C.as_s32 &= 0xF7FFFFFF;
    ((S_8014EC54_0 *)arg0)->unk_9E.s = 5;
    ((S_8014EC54_0 *)arg0)->unk_A4 = 0;
    ((S_8014EC54_0 *)arg0)->unk_9B++;

state_one:
    remaining = ((S_8014EC54_0 *)arg0)->unk_9E.s;
    ((S_8014EC54_0 *)arg0)->unk_90 -= ((S_8014EC54_0 *)arg0)->unk_A4;
    if (remaining != 0) {
        tile_x = ((Rec_D_80082E80 *)arg2)->unk_24;
        x = ((Rec_D_800E3D7C *)arg1)->unk_00.at02_s16.v;
        tile_x <<= 6;
        x -= 0x20;

        ((Rec_D_800E3D7C *)arg1)->unk_0C.as_s32 = ((tile_x - x) << 16) / remaining;

        y = ((Rec_D_800E3D7C *)arg1)->unk_04.at02_s16.v;
        y -= 0x20;
        ((Rec_D_800E3D7C *)arg1)->unk_10.at00_s32.v =
            (((((Rec_D_80082E80 *)arg2)->unk_25 << 6) - y) << 16) /
            ((S_8014EC54_0 *)arg0)->unk_9E.s;

        ((S_8014EC54_0 *)arg0)->unk_A4 =
            (-func_800644B8(((S_8014EC54_0 *)arg0)->unk_9E.s * 0x199)) << 10;
    }

    sum = ((S_8014EC54_0 *)arg0)->unk_90;
    velocity = ((S_8014EC54_0 *)arg0)->unk_A4;
    counter = ((S_8014EC54_0 *)arg0)->unk_9E.u;
    sum += velocity;
    counter -= 1;
    ((S_8014EC54_0 *)arg0)->unk_9E.u = counter;
    ((S_8014EC54_0 *)arg0)->unk_90 = sum;
    if ((counter << 16) >= 0) {
        goto state_two;
    }

    ((S_8014EC54_0 *)arg0)->unk_90 = 0;
    ((S_8014EC54_0 *)arg0)->unk_98 &= 0xFFF7;
    ((Rec_D_800E3D7C *)arg3)->unk_1C.as_s32 |= 0x08000000;
    ((S_8014EC54_0 *)arg0)->unk_9B++;

state_two:
    if (((Rec_D_800E3D7C *)arg3)->unk_1C.as_s32 & 0x08000000) {
        ((S_8014EC54_0 *)arg0)->unk_98 &= 0xFFF7;
        ((Rec_D_800E3D7C *)arg1)->unk_14.as_s32 = 0;
        ((Rec_D_800E3D7C *)arg1)->unk_10.at00_s32.v = 0;
        ((Rec_D_800E3D7C *)arg1)->unk_0C.as_s32 = 0;
        func_800A2B04(arg1, ((Rec_D_80082E80 *)arg2)->unk_24, ((Rec_D_80082E80 *)arg2)->unk_25);
        (*(u8 * *)((u8 *)arg2 + 0x2C)) = D_801519B8;
        func_80047784(
            arg2,
            D_801519B8[((D_80083228 + ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 + 0x100) >> 9) & 7],
            0);
        ((S_8014EC54_0 *)arg0)->unk_9B++;
    }
    goto decrement_timer;

state_three:
    if (((Rec_D_80082E80 *)arg2)->unk_2C.as_pu8 == D_80151988) {
        goto decrement_timer;
    }
    (*(u8 * *)((u8 *)arg2 + 0x2C)) = D_80151988;
    func_80047784(
        arg2,
        D_80151988[((D_80083228 + ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 + 0x100) >> 9) & 7],
        0);

decrement_timer:
    timer = ((S_8014EC54_0 *)arg0)->unk_96 - 1;
    ((S_8014EC54_0 *)arg0)->unk_96 = timer;
    if ((timer << 16) > 0) {
        return;
    }

    ((Rec_D_800E3D7C *)arg1)->unk_14.as_s32 = 0;
    ((Rec_D_800E3D7C *)arg1)->unk_10.at00_s32.v = 0;
    ((Rec_D_800E3D7C *)arg1)->unk_0C.as_s32 = 0;
    func_800A2B04(arg1, ((Rec_D_80082E80 *)arg2)->unk_24, ((Rec_D_80082E80 *)arg2)->unk_25);
    func_800AD594(arg3, 4);
    func_800A4ACC(arg3);

    global_base = (u8 *)&D_80083460;
    if (((S_8014EC54_4 *)global_base)->unk_08.s != 0) {
        ((S_8014EC54_4 *)global_base)->unk_08.u--;
    }

    flags = ((Rec_D_800E3D7C *)arg3)->unk_1C.as_s32;
    if (flags & 0x2000) {
        if (((Rec_D_800E3D7C *)arg3)->unk_44.at02_u16.v & 0x8000) {
            ((Rec_D_800E3D7C *)arg3)->unk_44.at02_u16.v &= 0x7FFF;
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
    ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 = func_800A0818(
        ((Rec_D_80082E80 *)arg2)->unk_24,
        ((Rec_D_80082E80 *)arg2)->unk_25,
        ((S_8014EC54_5 *)map_base)->unk_24,
        ((S_8014EC54_5 *)map_base)->unk_25,
        &sp18);

collision_check:
    if ((func_800AD9B4(arg2, arg3) << 16) > 0) {
        ((S_8014EC54_0 *)arg0)->unk_8C = &D_8014D7F4;
        func_800A9A04(arg3);
    }
}
