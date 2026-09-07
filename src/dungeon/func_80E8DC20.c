#include "common.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_80173420_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    union { u16 s; s16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
} S_80173420_0;   /* arg0 in func_80173420 */






extern void func_800A2B04();
extern void func_800AAA54();
extern void func_800AD4D0();

extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern s32 D_80083460;
extern u8 D_801710F4[];
extern u8 D_80174F10[];

void func_80173420(S_80173420_0 *arg0, Rec_D_800E3D7C *arg1, Rec_D_80082E80 *arg2, void *arg3)
{
    s16 *temp_a0_4;
    s32 temp_a0_2;
    s32 temp_a0_3;
    s32 temp_s4;
    s32 temp_v1_2;
    s32 temp_v1_3;
    s32 var_v0;
    s32 var_v0_2;
    s32 value;
    s32 *state;
    s16 *temp_v0_base;
    s32 temp_a0;
    s32 temp_v1;
    u16 var_v1;
    s32 ax;
    s32 dy;
    s32 ax2;
    s32 dy2;

    temp_a0 = arg0->unk_96.s - 1;
    temp_s4 = (((Rec_D_800E3D7C *)arg3)->unk_6A.as_u16 >> 9) & 7;
    temp_v1 = arg0->unk_9B;
    arg0->unk_96.s = temp_a0;
    switch (temp_v1) {
    case 0:
        goto state_0;
    case 1:
        goto state_1;
    case 2:
        goto state_2;
    default:
        return;
    }

state_0:
    func_800AD4D0(arg3);
    temp_v0_base = (s16 *)&D_8006CCD8;
    temp_v1_2 = temp_s4 * 2;
    arg1->unk_0C.as_s32 =
        *(s16 *)((u8 *)temp_v0_base + temp_v1_2) << 0x12;
    arg1->unk_10.at00_s32.v =
        *(s16 *)((u8 *)&D_8006CCE8 + temp_v1_2) << 0x12;
    arg0->unk_9B++;

    if (((Rec_D_800E3D7C *)arg3)->unk_28 == 0) {
        goto start_action;
    }
    if (arg2->unk_14.at00_u16.v & 0x8000) {
        arg0->unk_96.s = 0;
        arg0->unk_9B = 2;
        return;
    }

    var_v1 = 6;
    if (((Rec_D_800E3D7C *)arg3)->unk_1C.as_s32 & 0x228) {
        var_v1 = 8;
    }
    arg0->unk_96.s = var_v1;

    temp_v1_3 = arg1->unk_0C.as_s32;
    var_v0 = temp_v1_3;
    if (temp_v1_3 < 0) {
        var_v0 = temp_v1_3 + 3;
    }
    temp_a0_2 = arg1->unk_10.at00_s32.v;
    arg1->unk_0C.as_s32 = temp_v1_3 - (var_v0 >> 2);
    var_v0_2 = temp_a0_2;
    if (temp_a0_2 < 0) {
        var_v0_2 = temp_a0_2 + 3;
    }
    arg1->unk_10.at00_s32.v = temp_a0_2 - (var_v0_2 >> 2);

state_1:
    temp_v0_base = (s16 *)&D_8006CCD8;
    temp_a0_3 = temp_s4 * 2;
    temp_a0_4 = (s16 *)((u8 *)&D_8006CCE8 + temp_a0_3);
    arg1->unk_0C.as_s32 -=
        *(s16 *)((u8 *)temp_v0_base + temp_a0_3) << 0xE;
    arg1->unk_10.at00_s32.v -= *temp_a0_4 << 0xE;

    if (arg0->unk_96.u != 0) {
        return;
    }
    if (((Rec_D_800E3D7C *)arg3)->unk_28 != 0) {
        goto increment_state;
    }

start_action:
    arg1->unk_14.as_s32 = 0;
    arg1->unk_10.at00_s32.v = 0;
    arg1->unk_0C.as_s32 = 0;
    func_800AAA54(arg0, arg1, arg2, D_80174F10);
    return;

increment_state:
    arg0->unk_96.s = 6;
    arg0->unk_9B++;
    return;

state_2:
    if ((temp_a0 << 0x10) != 0) {
        ax = arg2->unk_24 << 6;
        dy = arg1->unk_00.at02_s16.v - 0x20;
        arg1->unk_0C.as_s32 = (ax - dy) << 0x10 >> 1;
        ax2 = arg2->unk_25 << 6;
        dy2 = arg1->unk_04.at02_s16.v - 0x20;
        arg1->unk_10.at00_s32.v = (ax2 - dy2) << 0x10 >> 1;

        if (arg0->unk_96.u > 0) {
            return;
        }
    }

    arg1->unk_14.as_s32 = 0;
    arg1->unk_10.at00_s32.v = 0;
    arg1->unk_0C.as_s32 = 0;
    func_800A2B04(arg1, arg2->unk_24, arg2->unk_25);

    state = &D_80083460;
    value = state[4];
    if (value == (s32)((u8 *)arg3 - 0x20)) {
        state[4] = value & 0x7FFFFFFF;
    }
    arg0->unk_8C = D_801710F4;
}
