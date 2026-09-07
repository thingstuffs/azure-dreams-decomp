#include "common.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_80082E80.h"


typedef struct S_80172EF4_1 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    union { s16 s; u16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
} S_80172EF4_1;   /* arg0 in func_80172EF4 */





extern void func_80047784();
extern void func_800A2B04();
extern void func_800AAA54();
extern void func_800AD4D0();

extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern s16 D_80083228;
extern s32 D_80083460;
extern u8 D_80170E5C[];
extern u8 D_80173D0C[];
extern s32 D_80173D24;

void func_80172EF4(void *arg0, void *arg1, void *arg2, void *arg3)
{
    s16 timer;
    s16 *temp_v0_base;
    s16 *temp_a0_4;
    s32 direction;
    s32 temp_v1_2;
    s32 temp_v1_3;
    s32 temp_a0_2;
    s32 temp_a0_3;
    s32 var_v0;
    s32 var_v0_2;
    s32 ax;
    s32 dy;
    s32 ax2;
    s32 dy2;
    s32 value;
    s32 *state;

    direction = (((Rec_D_800E3D7C *)arg3)->unk_6A.as_u16 >> 9) & 7;

    switch (((S_80172EF4_1 *)arg0)->unk_9B) {
    case 0:
        func_800AD4D0(arg3);
        temp_v0_base = (s16 *)&D_8006CCD8;
        temp_v1_2 = direction * 2;
        ((Rec_D_800E3D7C *)arg1)->unk_0C.as_s32 =
            *(s16 *)((u8 *)temp_v0_base + temp_v1_2) << 0x12;
        ((Rec_D_800E3D7C *)arg1)->unk_10.at00_s32.v =
            *(s16 *)((u8 *)&D_8006CCE8 + temp_v1_2) << 0x12;
        ((S_80172EF4_1 *)arg0)->unk_9B++;

        if (((Rec_D_800E3D7C *)arg3)->unk_28 == 0) {
            goto start_action;
        }
        if (((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0x8000) {
            ((S_80172EF4_1 *)arg0)->unk_96.s = 0;
            ((S_80172EF4_1 *)arg0)->unk_9B = 2;
            return;
        }

        timer = -1;
        if (((Rec_D_800E3D7C *)arg3)->unk_1C.as_s32 & 0x228) {
            timer = 8;
        }
        ((S_80172EF4_1 *)arg0)->unk_96.s = timer;

        temp_v1_3 = ((Rec_D_800E3D7C *)arg1)->unk_0C.as_s32;
        var_v0 = temp_v1_3;
        if (temp_v1_3 < 0) {
            var_v0 = temp_v1_3 + 3;
        }
        temp_a0_2 = ((Rec_D_800E3D7C *)arg1)->unk_10.at00_s32.v;
        ((Rec_D_800E3D7C *)arg1)->unk_0C.as_s32 = temp_v1_3 - (var_v0 >> 2);
        var_v0_2 = temp_a0_2;
        if (temp_a0_2 < 0) {
            var_v0_2 = temp_a0_2 + 3;
        }
        ((Rec_D_800E3D7C *)arg1)->unk_10.at00_s32.v = temp_a0_2 - (var_v0_2 >> 2);
        /* fall through */

    case 1:
        temp_v0_base = (s16 *)&D_8006CCD8;
        temp_a0_3 = direction * 2;
        temp_a0_4 = (s16 *)((u8 *)&D_8006CCE8 + temp_a0_3);
        ((Rec_D_800E3D7C *)arg1)->unk_0C.as_s32 -=
            *(s16 *)((u8 *)temp_v0_base + temp_a0_3) << 0xF;
        ((Rec_D_800E3D7C *)arg1)->unk_10.at00_s32.v -= *temp_a0_4 << 0xF;

        if (((S_80172EF4_1 *)arg0)->unk_96.s > 0) {
            ((S_80172EF4_1 *)arg0)->unk_96.s = ((S_80172EF4_1 *)arg0)->unk_96.u - 1;
        } else if (((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0x6000) {
            ((S_80172EF4_1 *)arg0)->unk_96.s = 0;
        }
        if (((S_80172EF4_1 *)arg0)->unk_96.s != 0) {
            return;
        }
        if (((Rec_D_800E3D7C *)arg3)->unk_28 != 0) {
            goto increment_state;
        }

start_action:
        ((Rec_D_800E3D7C *)arg1)->unk_14.as_s32 = 0;
        ((Rec_D_800E3D7C *)arg1)->unk_10.at00_s32.v = 0;
        ((Rec_D_800E3D7C *)arg1)->unk_0C.as_s32 = 0;
        func_800AAA54(arg0, arg1, arg2, &D_80173D24);
        return;

increment_state:
        ((S_80172EF4_1 *)arg0)->unk_96.s = 4;
        ((S_80172EF4_1 *)arg0)->unk_9B++;
        return;

    case 2:
        if (((S_80172EF4_1 *)arg0)->unk_96.s != 0) {
            ax = ((Rec_D_80082E80 *)arg2)->unk_24 << 6;
            dy = ((Rec_D_800E3D7C *)arg1)->unk_00.at02_s16.v - 0x20;
            ((Rec_D_800E3D7C *)arg1)->unk_0C.as_s32 = (ax - dy) << 0x10 >> 1;
            ax2 = ((Rec_D_80082E80 *)arg2)->unk_25 << 6;
            dy2 = ((Rec_D_800E3D7C *)arg1)->unk_04.at02_s16.v - 0x20;
            ((Rec_D_800E3D7C *)arg1)->unk_10.at00_s32.v = (ax2 - dy2) << 0x10 >> 1;
        }

        timer = ((S_80172EF4_1 *)arg0)->unk_96.u - 1;
        ((S_80172EF4_1 *)arg0)->unk_96.s = timer;
        if ((s32)(timer << 16) > 0) {
            return;
        }

        ((Rec_D_800E3D7C *)arg1)->unk_14.as_s32 = 0;
        ((Rec_D_800E3D7C *)arg1)->unk_10.at00_s32.v = 0;
        ((Rec_D_800E3D7C *)arg1)->unk_0C.as_s32 = 0;
        func_800A2B04(arg1, ((Rec_D_80082E80 *)arg2)->unk_24, ((Rec_D_80082E80 *)arg2)->unk_25);

        (*(void * *)((u8 *)arg2 + 0x2C)) = D_80173D0C;
        func_80047784(arg2,
            D_80173D0C[((D_80083228 + ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 + 0x100) >> 9) & 7],
            0);

        state = &D_80083460;
        value = state[4];
        if (value == (s32)((u8 *)arg3 - 0x20)) {
            state[4] = value & 0x7FFFFFFF;
        }
        ((S_80172EF4_1 *)arg0)->unk_8C = D_80170E5C;
        return;

    default:
        return;
    }
}
