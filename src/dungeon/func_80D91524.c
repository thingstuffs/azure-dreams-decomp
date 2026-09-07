#include "common.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_80082E80.h"


typedef struct S_80172D24_1 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    union { u16 s; s16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
} S_80172D24_1;   /* arg0 in func_80172D24 */





extern void func_80047784();
extern void func_800A2B04();
extern void func_800AAA54();
extern void func_800AD4D0();

extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern s16 D_80083228;
extern s32 D_80083460;
extern u8 D_80170E68;
extern u8 D_80173874[];

void func_80172D24(void *arg0, void *arg1, void *arg2, void *arg3)
{
    s16 *temp_a0_3;
    s16 *temp_v0_base;
    s16 temp_a0;
    s16 temp_v0;
    s16 var_v1;
    s32 temp_a0_2;
    s32 temp_a0_4;
    s32 temp_s4;
    s32 temp_v1_2;
    s32 temp_v1_3;
    s32 var_v0_2;
    s32 var_v0_3;
    s32 ax;
    s32 dy;
    s32 ax2;
    s32 dy2;
    s32 *global;
    s32 value;
    u8 state;

    temp_s4 = (((Rec_D_800E3D7C *)arg3)->unk_6A.as_u16 >> 9) & 7;
    state = ((S_80172D24_1 *)arg0)->unk_9B;

    switch (state) {
    case 0:
        goto state_0;
    case 1:
        goto state_1;
    case 2:
        goto state_2;
    case 3:
        goto state_3;
    default:
        return;
    }

state_0:
    func_800AD4D0(arg3);
    if (((Rec_D_800E3D7C *)arg3)->unk_28 == 0) {
        goto start_action;
    }
    if (((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0x8000) {
        ((S_80172D24_1 *)arg0)->unk_96.s = 0;
        ((S_80172D24_1 *)arg0)->unk_9B = 3;
        return;
    }
    ((S_80172D24_1 *)arg0)->unk_96.s = 12;
    ((S_80172D24_1 *)arg0)->unk_9B++;

state_1:
    temp_v0 = ((S_80172D24_1 *)arg0)->unk_96.s - 1;
    ((S_80172D24_1 *)arg0)->unk_96.s = temp_v0;
    if ((temp_v0 << 16) != 0) {
        return;
    }

    (*(void * *)((u8 *)arg2 + 0x2C)) = D_80173874;
    func_80047784(arg2,
        D_80173874[((D_80083228 + ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 + 0x100) >> 9) & 7],
        0);

    temp_v0_base = (s16 *)&D_8006CCD8;
    temp_v1_2 = temp_s4 * 2;
    ((Rec_D_800E3D7C *)arg1)->unk_0C.as_s32 =
        *(s16 *)((u8 *)temp_v0_base + temp_v1_2) << 19;
    ((Rec_D_800E3D7C *)arg1)->unk_10.at00_s32.v =
        *(s16 *)((u8 *)&D_8006CCE8 + temp_v1_2) << 19;

    var_v1 = -1;
    if (((Rec_D_800E3D7C *)arg3)->unk_1C.as_s32 & 0x228) {
        var_v1 = 8;
    }
    ((S_80172D24_1 *)arg0)->unk_96.s = var_v1;

    temp_v1_3 = ((Rec_D_800E3D7C *)arg1)->unk_0C.as_s32;
    var_v0_2 = temp_v1_3;
    if (temp_v1_3 < 0) {
        var_v0_2 = temp_v1_3 + 3;
    }
    temp_a0_4 = ((Rec_D_800E3D7C *)arg1)->unk_10.at00_s32.v;
    ((Rec_D_800E3D7C *)arg1)->unk_0C.as_s32 = temp_v1_3 - (var_v0_2 >> 2);
    var_v0_3 = temp_a0_4;
    if (temp_a0_4 < 0) {
        var_v0_3 = temp_a0_4 + 3;
    }
    ((Rec_D_800E3D7C *)arg1)->unk_10.at00_s32.v = temp_a0_4 - (var_v0_3 >> 2);
    temp_v0 = ((S_80172D24_1 *)arg0)->unk_9B + 1;
    goto store_state;

state_2:
    temp_v0_base = (s16 *)&D_8006CCD8;
    temp_a0_2 = temp_s4 * 2;
    temp_a0_3 = (s16 *)((u8 *)&D_8006CCE8 + temp_a0_2);
    ((Rec_D_800E3D7C *)arg1)->unk_0C.as_s32 -=
        *(s16 *)((u8 *)temp_v0_base + temp_a0_2) << 16;
    ((Rec_D_800E3D7C *)arg1)->unk_10.at00_s32.v -= *temp_a0_3 << 16;

    if (((S_80172D24_1 *)arg0)->unk_96.u > 0) {
        ((S_80172D24_1 *)arg0)->unk_96.s--;
    } else if (((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0x6000) {
        ((S_80172D24_1 *)arg0)->unk_96.s = 0;
    }
    if (((S_80172D24_1 *)arg0)->unk_96.u != 0) {
        return;
    }
    if (((Rec_D_800E3D7C *)arg3)->unk_28 != 0) {
        var_v1 = 8;
        goto increment_state;
    }

start_action:
    ((Rec_D_800E3D7C *)arg1)->unk_14.as_s32 = 0;
    ((Rec_D_800E3D7C *)arg1)->unk_10.at00_s32.v = 0;
    ((Rec_D_800E3D7C *)arg1)->unk_0C.as_s32 = 0;
    func_800AAA54(arg0, arg1, arg2, D_80173874);
    return;

increment_state:
    temp_v0 = ((S_80172D24_1 *)arg0)->unk_9B + 1;
    ((S_80172D24_1 *)arg0)->unk_96.s = var_v1;

store_state:
    ((S_80172D24_1 *)arg0)->unk_9B = temp_v0;
    return;

state_3:
    temp_a0 = ((S_80172D24_1 *)arg0)->unk_96.u;
    if (temp_a0 != 0) {
        ax = ((Rec_D_80082E80 *)arg2)->unk_24 << 6;
        dy = ((Rec_D_800E3D7C *)arg1)->unk_00.at02_s16.v - 0x20;
        ((Rec_D_800E3D7C *)arg1)->unk_0C.as_s32 = ((ax - dy) << 15) / temp_a0;

        ax2 = ((Rec_D_80082E80 *)arg2)->unk_25 << 6;
        dy2 = ((Rec_D_800E3D7C *)arg1)->unk_04.at02_s16.v - 0x20;
        ((Rec_D_800E3D7C *)arg1)->unk_10.at00_s32.v =
            ((ax2 - dy2) << 15) / ((S_80172D24_1 *)arg0)->unk_96.u;
    }

    temp_v0 = ((S_80172D24_1 *)arg0)->unk_96.s - 1;
    ((S_80172D24_1 *)arg0)->unk_96.s = temp_v0;
    if ((temp_v0 << 16) > 0) {
        return;
    }

    ((Rec_D_800E3D7C *)arg1)->unk_14.as_s32 = 0;
    ((Rec_D_800E3D7C *)arg1)->unk_10.at00_s32.v = 0;
    ((Rec_D_800E3D7C *)arg1)->unk_0C.as_s32 = 0;
    func_800A2B04(arg1, ((Rec_D_80082E80 *)arg2)->unk_24, ((Rec_D_80082E80 *)arg2)->unk_25);

    global = &D_80083460;
    value = *(s32 *)((u8 *)global + 0x10);
    if (value == (s32)((u8 *)arg3 - 0x20)) {
        *(s32 *)((u8 *)global + 0x10) = value & 0x7FFFFFFF;
    }
    ((S_80172D24_1 *)arg0)->unk_8C = &D_80170E68;
}
