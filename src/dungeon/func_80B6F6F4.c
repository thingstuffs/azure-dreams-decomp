#include "common.h"

typedef struct S_80172EF4_0 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0x8];
    u8 unk_28;
    u8 pad_29[0x1];
    s16 unk_2A;
    u8 pad_2C[0x3E];
    u16 unk_6A;
} S_80172EF4_0;   /* arg3 in func_80172EF4 */

typedef struct S_80172EF4_1 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    union { s16 s; u16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
} S_80172EF4_1;   /* arg0 in func_80172EF4 */

typedef struct S_80172EF4_2 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x4];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80172EF4_2;   /* arg1 in func_80172EF4 */

typedef struct S_80172EF4_3 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_80172EF4_3;   /* arg2 in func_80172EF4 */



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

    direction = (((S_80172EF4_0 *)arg3)->unk_6A >> 9) & 7;

    switch (((S_80172EF4_1 *)arg0)->unk_9B) {
    case 0:
        func_800AD4D0(arg3);
        temp_v0_base = (s16 *)&D_8006CCD8;
        temp_v1_2 = direction * 2;
        ((S_80172EF4_2 *)arg1)->unk_0C =
            *(s16 *)((u8 *)temp_v0_base + temp_v1_2) << 0x12;
        ((S_80172EF4_2 *)arg1)->unk_10 =
            *(s16 *)((u8 *)&D_8006CCE8 + temp_v1_2) << 0x12;
        ((S_80172EF4_1 *)arg0)->unk_9B++;

        if (((S_80172EF4_0 *)arg3)->unk_28 == 0) {
            goto start_action;
        }
        if (((S_80172EF4_3 *)arg2)->unk_14 & 0x8000) {
            ((S_80172EF4_1 *)arg0)->unk_96.s = 0;
            ((S_80172EF4_1 *)arg0)->unk_9B = 2;
            return;
        }

        timer = -1;
        if (((S_80172EF4_0 *)arg3)->unk_1C & 0x228) {
            timer = 8;
        }
        ((S_80172EF4_1 *)arg0)->unk_96.s = timer;

        temp_v1_3 = ((S_80172EF4_2 *)arg1)->unk_0C;
        var_v0 = temp_v1_3;
        if (temp_v1_3 < 0) {
            var_v0 = temp_v1_3 + 3;
        }
        temp_a0_2 = ((S_80172EF4_2 *)arg1)->unk_10;
        ((S_80172EF4_2 *)arg1)->unk_0C = temp_v1_3 - (var_v0 >> 2);
        var_v0_2 = temp_a0_2;
        if (temp_a0_2 < 0) {
            var_v0_2 = temp_a0_2 + 3;
        }
        ((S_80172EF4_2 *)arg1)->unk_10 = temp_a0_2 - (var_v0_2 >> 2);
        /* fall through */

    case 1:
        temp_v0_base = (s16 *)&D_8006CCD8;
        temp_a0_3 = direction * 2;
        temp_a0_4 = (s16 *)((u8 *)&D_8006CCE8 + temp_a0_3);
        ((S_80172EF4_2 *)arg1)->unk_0C -=
            *(s16 *)((u8 *)temp_v0_base + temp_a0_3) << 0xF;
        ((S_80172EF4_2 *)arg1)->unk_10 -= *temp_a0_4 << 0xF;

        if (((S_80172EF4_1 *)arg0)->unk_96.s > 0) {
            ((S_80172EF4_1 *)arg0)->unk_96.s = ((S_80172EF4_1 *)arg0)->unk_96.u - 1;
        } else if (((S_80172EF4_3 *)arg2)->unk_14 & 0x6000) {
            ((S_80172EF4_1 *)arg0)->unk_96.s = 0;
        }
        if (((S_80172EF4_1 *)arg0)->unk_96.s != 0) {
            return;
        }
        if (((S_80172EF4_0 *)arg3)->unk_28 != 0) {
            goto increment_state;
        }

start_action:
        ((S_80172EF4_2 *)arg1)->unk_14 = 0;
        ((S_80172EF4_2 *)arg1)->unk_10 = 0;
        ((S_80172EF4_2 *)arg1)->unk_0C = 0;
        func_800AAA54(arg0, arg1, arg2, &D_80173D24);
        return;

increment_state:
        ((S_80172EF4_1 *)arg0)->unk_96.s = 4;
        ((S_80172EF4_1 *)arg0)->unk_9B++;
        return;

    case 2:
        if (((S_80172EF4_1 *)arg0)->unk_96.s != 0) {
            ax = ((S_80172EF4_3 *)arg2)->unk_24 << 6;
            dy = ((S_80172EF4_2 *)arg1)->unk_02 - 0x20;
            ((S_80172EF4_2 *)arg1)->unk_0C = (ax - dy) << 0x10 >> 1;
            ax2 = ((S_80172EF4_3 *)arg2)->unk_25 << 6;
            dy2 = ((S_80172EF4_2 *)arg1)->unk_06 - 0x20;
            ((S_80172EF4_2 *)arg1)->unk_10 = (ax2 - dy2) << 0x10 >> 1;
        }

        timer = ((S_80172EF4_1 *)arg0)->unk_96.u - 1;
        ((S_80172EF4_1 *)arg0)->unk_96.s = timer;
        if ((s32)(timer << 16) > 0) {
            return;
        }

        ((S_80172EF4_2 *)arg1)->unk_14 = 0;
        ((S_80172EF4_2 *)arg1)->unk_10 = 0;
        ((S_80172EF4_2 *)arg1)->unk_0C = 0;
        func_800A2B04(arg1, ((S_80172EF4_3 *)arg2)->unk_24, ((S_80172EF4_3 *)arg2)->unk_25);

        (*(void * *)((u8 *)arg2 + 0x2C)) = D_80173D0C;
        func_80047784(arg2,
            D_80173D0C[((D_80083228 + ((S_80172EF4_0 *)arg3)->unk_2A + 0x100) >> 9) & 7],
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
