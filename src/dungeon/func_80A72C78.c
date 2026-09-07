#include "common.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_D_800E3D7C.h"

typedef struct S_80172478_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    s32 unk_90;
    u8 pad_94[0x2];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x8];
    s32 unk_A4;
    union { s16 s; u16 u; } unk_A8;   /* accessed as both */
} S_80172478_0;   /* arg0 in func_80172478 */


typedef struct S_80172478_2 {
    u8 pad_00[0x1C];
    union { u32 s; s32 u; } unk_1C;   /* accessed as both */
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
} S_80172478_2;   /* arg3 in func_80172478 */


typedef struct S_80172478_4 {
    u8 pad_00[0x8];
    union { s16 s; u16 u; } unk_08;   /* accessed as both */
} S_80172478_4;   /* global_base in func_80172478 */

typedef struct S_80172478_5 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80172478_5;   /* map_base in func_80172478 */



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
extern u8 D_80170E54;
extern u8 D_80174160[];
extern u8 D_80174168[];

void func_80172478(void *arg0, void *arg1, void *arg2, void *arg3)
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

    state = ((S_80172478_0 *)arg0)->unk_9B;
    if (state == 1) {
        goto state_one;
    }
    if (state < 2) {
        if (state == 0) {
            goto state_zero;
        }
        goto tick;
    }
    if (state == 2) {
        goto state_two;
    }
    goto tick;

state_zero:
    if (!(((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0x6000)) {
        goto tick;
    }
    (*(u8 * *)((u8 *)arg2 + 0x2C)) = D_80174160;
    func_80047784(
        arg2,
        D_80174160[((D_80083228 + ((S_80172478_2 *)arg3)->unk_2A + 0x100) >> 9) & 7],
        0);
    ((S_80172478_0 *)arg0)->unk_98 |= 8;
    ((S_80172478_2 *)arg3)->unk_1C.s &= 0xF7FFFFFF;
    ((S_80172478_0 *)arg0)->unk_A8.s = 5;
    ((S_80172478_0 *)arg0)->unk_A4 = 0;
    ((S_80172478_0 *)arg0)->unk_9B++;

state_one:
    remaining = ((S_80172478_0 *)arg0)->unk_A8.s;
    ((S_80172478_0 *)arg0)->unk_90 -= ((S_80172478_0 *)arg0)->unk_A4;
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
            ((S_80172478_0 *)arg0)->unk_A8.s;

        ((S_80172478_0 *)arg0)->unk_A4 =
            (-func_800644B8(((S_80172478_0 *)arg0)->unk_A8.s * 0x199)) << 10;
    }

    sum = ((S_80172478_0 *)arg0)->unk_90;
    velocity = ((S_80172478_0 *)arg0)->unk_A4;
    counter = ((S_80172478_0 *)arg0)->unk_A8.u;
    sum += velocity;
    counter -= 1;
    ((S_80172478_0 *)arg0)->unk_A8.u = counter;
    ((S_80172478_0 *)arg0)->unk_90 = sum;
    if ((counter << 16) >= 0) {
        goto tick;
    }

    ((S_80172478_0 *)arg0)->unk_90 = 0;
    ((S_80172478_0 *)arg0)->unk_98 &= 0xFFF7;
    ((S_80172478_2 *)arg3)->unk_1C.s |= 0x08000000;
    goto advance_state;

state_two:
    if (((S_80172478_2 *)arg3)->unk_1C.s & 0x08000000) {
        ((S_80172478_0 *)arg0)->unk_98 &= 0xFFF7;
        ((Rec_D_800E3D7C *)arg1)->unk_14.as_s32 = 0;
        ((Rec_D_800E3D7C *)arg1)->unk_10.at00_s32.v = 0;
        ((Rec_D_800E3D7C *)arg1)->unk_0C.as_s32 = 0;
        func_800A2B04(arg1, ((Rec_D_80082E80 *)arg2)->unk_24, ((Rec_D_80082E80 *)arg2)->unk_25);
        (*(u8 * *)((u8 *)arg2 + 0x2C)) = D_80174168;
        func_80047784(
            arg2,
            D_80174168[((D_80083228 + ((S_80172478_2 *)arg3)->unk_2A + 0x100) >> 9) & 7],
            0);

advance_state:
        ((S_80172478_0 *)arg0)->unk_9B++;
    }

tick:
    timer = ((S_80172478_0 *)arg0)->unk_96 - 1;
    ((S_80172478_0 *)arg0)->unk_96 = timer;
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
    if (((S_80172478_4 *)global_base)->unk_08.s != 0) {
        ((S_80172478_4 *)global_base)->unk_08.u--;
    }

    flags = ((S_80172478_2 *)arg3)->unk_1C.u;
    if (flags & 0x2000) {
        if (((S_80172478_2 *)arg3)->unk_46 & 0x8000) {
            ((S_80172478_2 *)arg3)->unk_46 &= 0x7FFF;
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
    ((S_80172478_2 *)arg3)->unk_2A = func_800A0818(
        ((Rec_D_80082E80 *)arg2)->unk_24,
        ((Rec_D_80082E80 *)arg2)->unk_25,
        ((S_80172478_5 *)map_base)->unk_24,
        ((S_80172478_5 *)map_base)->unk_25,
        &sp18);

collision_check:
    if ((func_800AD9B4(arg2, arg3) << 16) > 0) {
        ((S_80172478_0 *)arg0)->unk_8C = &D_80170E54;
        func_800A9A04(arg3);
    }
}
