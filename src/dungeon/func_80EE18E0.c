#include "common.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_D_800E3D7C.h"

typedef struct S_801730E0_0 {
    u8 pad_00[0x8C];
    s32 * unk_8C;
    s32 unk_90;
    u8 pad_94[0x2];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x2];
    union { u16 s; s16 u; } unk_9E;   /* accessed as both */
    s32 unk_A0;
} S_801730E0_0;   /* arg0 in func_801730E0 */

typedef struct S_801730E0_1 {
    u8 pad_00[0x1C];
    union { u32 s; s32 u; } unk_1C;   /* accessed as both */
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
} S_801730E0_1;   /* arg3 in func_801730E0 */





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
extern s32 D_80171CE8;
extern u8 D_80174EB8[];
extern u8 D_80174ED0[];
extern u8 D_80174ED8[];

void func_801730E0(void *arg0, void *arg1, void *arg2, void *arg3)
{
    s32 scratch;
    s32 state;
    s32 remaining;
    s32 flags;
    s32 tile_x;
    s32 position;
    s32 position_y;
    s16 next_timer;
    s16 *global;
    u16 countdown;
    u8 *table;

    state = ((S_801730E0_0 *)arg0)->unk_9B;
    if (state == 1) {
        goto state_one;
    }
    if (state < 2) {
        if (state == 0) {
            goto state_zero;
        }
        goto update_countdown;
    }
    if (state == 2) {
        goto state_two;
    }
    if (state == 3) {
        goto state_three;
    }
    goto update_countdown;

state_zero:
    next_timer = ((S_801730E0_0 *)arg0)->unk_9E.s - 1;
    ((S_801730E0_0 *)arg0)->unk_9E.s = next_timer;
    if ((next_timer << 16) != 0) {
        goto update_countdown;
    }

    (*(u8 * *)((u8 *)arg2 + 0x2C)) = D_80174ED0;
    func_80047784(
        arg2,
        D_80174ED0[((D_80083228 + ((S_801730E0_1 *)arg3)->unk_2A + 0x100) >> 9) & 7],
        0);
    ((S_801730E0_0 *)arg0)->unk_98 |= 8;
    ((S_801730E0_1 *)arg3)->unk_1C.s &= 0xF7FFFFFF;
    ((S_801730E0_0 *)arg0)->unk_9E.u = 5;
    ((S_801730E0_0 *)arg0)->unk_A0 = 0;
    ((S_801730E0_0 *)arg0)->unk_9B++;

state_one:
    remaining = ((S_801730E0_0 *)arg0)->unk_9E.u;
    ((S_801730E0_0 *)arg0)->unk_90 -= ((S_801730E0_0 *)arg0)->unk_A0;
    if (remaining != 0) {
        tile_x = ((Rec_D_80082E80 *)arg2)->unk_24;
        position = ((Rec_D_800E3D7C *)arg1)->unk_00.at02_s16.v;
        tile_x <<= 6;
        position -= 0x20;
        ((Rec_D_800E3D7C *)arg1)->unk_0C.as_s32 = ((tile_x - position) << 16) / remaining;

        position_y = ((Rec_D_800E3D7C *)arg1)->unk_04.at02_s16.v;
        position_y -= 0x20;
        ((Rec_D_800E3D7C *)arg1)->unk_10.at00_s32.v =
            (((((Rec_D_80082E80 *)arg2)->unk_25 << 6) - position_y) << 16) /
            ((S_801730E0_0 *)arg0)->unk_9E.u;
        ((S_801730E0_0 *)arg0)->unk_A0 =
            (-func_800644B8(((S_801730E0_0 *)arg0)->unk_9E.u * 0x199)) << 10;
    }

    ((S_801730E0_0 *)arg0)->unk_90 += ((S_801730E0_0 *)arg0)->unk_A0;
    next_timer = ((S_801730E0_0 *)arg0)->unk_9E.s - 1;
    ((S_801730E0_0 *)arg0)->unk_9E.s = next_timer;
    if (next_timer < 0) {
        ((S_801730E0_0 *)arg0)->unk_90 = 0;
        ((S_801730E0_0 *)arg0)->unk_98 &= 0xFFF7;
        ((S_801730E0_1 *)arg3)->unk_1C.s |= 0x08000000;
        ((S_801730E0_0 *)arg0)->unk_9B++;
    }

state_two:
    if (((S_801730E0_1 *)arg3)->unk_1C.s & 0x08000000) {
        ((S_801730E0_0 *)arg0)->unk_98 &= 0xFFF7;
        ((Rec_D_800E3D7C *)arg1)->unk_14.as_s32 = 0;
        ((Rec_D_800E3D7C *)arg1)->unk_10.at00_s32.v = 0;
        ((Rec_D_800E3D7C *)arg1)->unk_0C.as_s32 = 0;
        func_800A2B04(arg1, ((Rec_D_80082E80 *)arg2)->unk_24, ((Rec_D_80082E80 *)arg2)->unk_25);

        (*(u8 * *)((u8 *)arg2 + 0x2C)) = D_80174ED8;
        func_80047784(
            arg2,
            D_80174ED8[((D_80083228 + ((S_801730E0_1 *)arg3)->unk_2A + 0x100) >> 9) & 7],
            0);
        ((S_801730E0_0 *)arg0)->unk_9B++;
    }
    goto update_countdown;

state_three:
    table = D_80174EB8;
    if (((Rec_D_80082E80 *)arg2)->unk_2C.as_pu8 != table) {
        (*(u8 * *)((u8 *)arg2 + 0x2C)) = table;
        func_80047784(
            arg2,
            table[((D_80083228 + ((S_801730E0_1 *)arg3)->unk_2A + 0x100) >> 9) & 7],
            0);
    }

update_countdown:
    countdown = ((S_801730E0_0 *)arg0)->unk_96 - 1;
    ((S_801730E0_0 *)arg0)->unk_96 = countdown;
    if ((s16)countdown > 0) {
        return;
    }

    ((Rec_D_800E3D7C *)arg1)->unk_14.as_s32 = 0;
    ((Rec_D_800E3D7C *)arg1)->unk_10.at00_s32.v = 0;
    ((Rec_D_800E3D7C *)arg1)->unk_0C.as_s32 = 0;
    func_800A2B04(arg1, ((Rec_D_80082E80 *)arg2)->unk_24, ((Rec_D_80082E80 *)arg2)->unk_25);
    func_800AD594(arg3, 4);
    func_800A4ACC(arg3);

    global = (s16 *)&D_80083460;
    if (global[4] != 0) {
        global[4]--;
    }

    flags = ((S_801730E0_1 *)arg3)->unk_1C.u;
    if (flags & 0x2000) {
        if (((S_801730E0_1 *)arg3)->unk_46 & 0x8000) {
            ((S_801730E0_1 *)arg3)->unk_46 &= 0x7FFF;
        }
    } else if (!(flags & 0x410)) {
        if (flags & 0x20000) {
            ((S_801730E0_1 *)arg3)->unk_2A = func_800A0818(
                ((Rec_D_80082E80 *)arg2)->unk_24, ((Rec_D_80082E80 *)arg2)->unk_25,
                D_80082E80[0x24], D_80082E80[0x25], &scratch);
        }
    }

    if ((func_800AD9B4(arg2, arg3) << 16) > 0) {
        ((S_801730E0_0 *)arg0)->unk_8C = &D_80171CE8;
        func_800A9A04(arg3);
    }
}
