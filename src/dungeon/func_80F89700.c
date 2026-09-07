#include "common.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_80172F00_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    u8 pad_90[0x6];
    union { s16 s; volatile u16 u; u16 p; } unk_96;   /* accessed as both */
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
} S_80172F00_0;   /* arg0 in func_80172F00 */






extern void func_80047784();
extern void func_800A2B04();
extern void func_800AAA54();
extern void func_800AD4D0();

extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern s16 D_80083228;
extern s32 D_80083460;
extern u8 D_80171138[];
extern u8 D_80174AD4[];
extern u8 D_80174ADC[];

void func_80172F00(void *arg0, void *arg1, void *arg2, void *arg3)
{
    s16 timer_signed;
    s32 index;
    s32 x;
    s32 y;
    s32 rounded_x;
    s32 rounded_y;
    s32 value;
    s32 *global_state;
    s32 state;
    u16 timer;

    state = ((S_80172F00_0 *)arg0)->unk_9B;
    index = (((Rec_D_800E3D7C *)arg3)->unk_6A.as_u16 >> 9) & 7;

    if (state == 1) {
        goto state_1;
    }
    if (state < 2) {
        if (state == 0) {
            goto state_0;
        }
        return;
    }
    if (state == 2) {
        goto state_2;
    }
    return;

state_0:
            func_800AD4D0(arg3);
            if (((Rec_D_800E3D7C *)arg3)->unk_28 == 0) {
                ((Rec_D_800E3D7C *)arg1)->unk_14.as_s32 = 0;
                ((Rec_D_800E3D7C *)arg1)->unk_10.at00_s32.v = 0;
                ((Rec_D_800E3D7C *)arg1)->unk_0C.as_s32 = 0;
                ((Rec_D_800E3D7C *)arg1)->unk_14.as_s32 = 0xFFFD0000;
                func_800AAA54(arg0, arg1, arg2, D_80174ADC);
                return;
            }

            {
                u32 mask_a0 = 0xF7FFFFFF;
                u32 mask_v1 = 0xFFFBFFFF;
                u32 flags;
                u16 field98;

                ((Rec_D_800E3D7C *)arg1)->unk_0C.as_s32 =
                    ((s16 *)&D_8006CCD8)[index] << 18;
                ((Rec_D_800E3D7C *)arg1)->unk_10.at00_s32.v =
                    ((s16 *)&D_8006CCE8)[index] << 18;
                ((Rec_D_800E3D7C *)arg1)->unk_14.as_s32 = 0x20000;

                field98 = ((S_80172F00_0 *)arg0)->unk_98;
                field98 |= 8;
                ((S_80172F00_0 *)arg0)->unk_98 = field98;
                flags = ((Rec_D_800E3D7C *)arg3)->unk_1C.as_u32;
                flags &= mask_a0;
                flags &= mask_v1;
                ((Rec_D_800E3D7C *)arg3)->unk_1C.as_u32 = flags;
            }

            ((S_80172F00_0 *)arg0)->unk_9B = ((S_80172F00_0 *)arg0)->unk_9B + 1;
            timer_signed = -1;
            if (((Rec_D_800E3D7C *)arg3)->unk_1C.as_u32 & 0x228) {
                timer_signed = 8;
            }
            ((S_80172F00_0 *)arg0)->unk_96.s = timer_signed;

            x = ((Rec_D_800E3D7C *)arg1)->unk_0C.as_s32;
            rounded_x = x;
            if (x < 0) {
                rounded_x = x + 3;
            }
            y = ((Rec_D_800E3D7C *)arg1)->unk_10.at00_s32.v;
            ((Rec_D_800E3D7C *)arg1)->unk_0C.as_s32 = x - (rounded_x >> 2);
            rounded_y = y;
            if (y < 0) {
                rounded_y = y + 3;
            }
            ((Rec_D_800E3D7C *)arg1)->unk_10.at00_s32.v = y - (rounded_y >> 2);
            return;

state_1:
    ((Rec_D_800E3D7C *)arg1)->unk_0C.as_s32 -=
        ((s16 *)&D_8006CCD8)[index] << 15;
    ((Rec_D_800E3D7C *)arg1)->unk_10.at00_s32.v -= ((s16 *)&D_8006CCE8)[index] << 15;

    timer_signed = ((S_80172F00_0 *)arg0)->unk_96.s;
    timer = ((S_80172F00_0 *)arg0)->unk_96.u;
    if (timer_signed > 0) {
        timer -= 1;
        ((S_80172F00_0 *)arg0)->unk_96.p = timer;
        goto check_timer;
    }
    if (((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0x6000) {
        ((S_80172F00_0 *)arg0)->unk_96.p = 0;
    }

check_timer:
    if (((S_80172F00_0 *)arg0)->unk_96.s != 0) {
        return;
    }
    if (((Rec_D_800E3D7C *)arg3)->unk_28 != 0) {
        goto increment_state;
    }

start_action:
    ((S_80172F00_0 *)arg0)->unk_9B = 0;
    ((Rec_D_800E3D7C *)arg1)->unk_10.at00_s32.v = 0;
    ((Rec_D_800E3D7C *)arg1)->unk_0C.as_s32 = 0;
    ((Rec_D_800E3D7C *)arg1)->unk_14.as_s32 = 0xFFFD0000;
    func_800AAA54(arg0, arg1, arg2, D_80174ADC);
    return;

increment_state:
    ((S_80172F00_0 *)arg0)->unk_96.s = 5;
    ((S_80172F00_0 *)arg0)->unk_9B = ((S_80172F00_0 *)arg0)->unk_9B + 1;
    return;

state_2:
    ((Rec_D_800E3D7C *)arg1)->unk_14.as_s32 = 0xFFFD0000;
    if (((S_80172F00_0 *)arg0)->unk_96.s != 0) {
        s32 scaled;
        s32 origin;

        scaled = ((Rec_D_80082E80 *)arg2)->unk_24 << 6;
        origin = ((Rec_D_800E3D7C *)arg1)->unk_00.at02_s16.v;
        origin -= 0x20;
        ((Rec_D_800E3D7C *)arg1)->unk_0C.as_s32 = (scaled - origin) << 15;
        scaled = ((Rec_D_80082E80 *)arg2)->unk_25 << 6;
        origin = ((Rec_D_800E3D7C *)arg1)->unk_04.at02_s16.v;
        origin -= 0x20;
        ((Rec_D_800E3D7C *)arg1)->unk_10.at00_s32.v = (scaled - origin) << 15;
    }

    timer = ((S_80172F00_0 *)arg0)->unk_96.p - 1;
    ((S_80172F00_0 *)arg0)->unk_96.p = timer;
    if ((timer << 16) > 0) {
        return;
    }

    ((Rec_D_800E3D7C *)arg1)->unk_14.as_s32 = 0;
    ((Rec_D_800E3D7C *)arg1)->unk_10.at00_s32.v = 0;
    ((Rec_D_800E3D7C *)arg1)->unk_0C.as_s32 = 0;
    func_800A2B04(arg1, ((Rec_D_80082E80 *)arg2)->unk_24, ((Rec_D_80082E80 *)arg2)->unk_25);

    ((S_80172F00_0 *)arg0)->unk_98 &= 0xFFF7;
    ((Rec_D_800E3D7C *)arg3)->unk_1C.as_u32 |= 0x08000000;
    ((Rec_D_800E3D7C *)arg3)->unk_1C.as_u32 |= 0x00040000;
    (*(u8 * *)((u8 *)arg2 + 0x2C)) = D_80174AD4;
    func_80047784(
        arg2,
        D_80174AD4[((D_80083228 + ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 + 0x100) >> 9) & 7],
        0);

    global_state = &D_80083460;
    value = global_state[4];
    if (value == (s32)((u8 *)arg3 - 0x20)) {
        global_state[4] = value & 0x7FFFFFFF;
    }
    ((S_80172F00_0 *)arg0)->unk_8C = D_80171138;
}

/* MECHANISM: Symbolic s16 indexing and C/10/14 store order reproduce both table-load regions.
   Block-scoped scaled/origin temporaries preserve the two addiu-before-subu sequences
   without extending the earlier rounding temporaries across the state-machine CFG. */
