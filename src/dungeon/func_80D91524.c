#include "common.h"

typedef struct S_80172D24_0 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0x8];
    u8 unk_28;
    u8 pad_29[0x1];
    s16 unk_2A;
    u8 pad_2C[0x3E];
    u16 unk_6A;
} S_80172D24_0;   /* arg3 in func_80172D24 */

typedef struct S_80172D24_1 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    union { u16 s; s16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
} S_80172D24_1;   /* arg0 in func_80172D24 */

typedef struct S_80172D24_2 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_80172D24_2;   /* arg2 in func_80172D24 */

typedef struct S_80172D24_3 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x4];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80172D24_3;   /* arg1 in func_80172D24 */



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

    temp_s4 = (((S_80172D24_0 *)arg3)->unk_6A >> 9) & 7;
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
    if (((S_80172D24_0 *)arg3)->unk_28 == 0) {
        goto start_action;
    }
    if (((S_80172D24_2 *)arg2)->unk_14 & 0x8000) {
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
        D_80173874[((D_80083228 + ((S_80172D24_0 *)arg3)->unk_2A + 0x100) >> 9) & 7],
        0);

    temp_v0_base = (s16 *)&D_8006CCD8;
    temp_v1_2 = temp_s4 * 2;
    ((S_80172D24_3 *)arg1)->unk_0C =
        *(s16 *)((u8 *)temp_v0_base + temp_v1_2) << 19;
    ((S_80172D24_3 *)arg1)->unk_10 =
        *(s16 *)((u8 *)&D_8006CCE8 + temp_v1_2) << 19;

    var_v1 = -1;
    if (((S_80172D24_0 *)arg3)->unk_1C & 0x228) {
        var_v1 = 8;
    }
    ((S_80172D24_1 *)arg0)->unk_96.s = var_v1;

    temp_v1_3 = ((S_80172D24_3 *)arg1)->unk_0C;
    var_v0_2 = temp_v1_3;
    if (temp_v1_3 < 0) {
        var_v0_2 = temp_v1_3 + 3;
    }
    temp_a0_4 = ((S_80172D24_3 *)arg1)->unk_10;
    ((S_80172D24_3 *)arg1)->unk_0C = temp_v1_3 - (var_v0_2 >> 2);
    var_v0_3 = temp_a0_4;
    if (temp_a0_4 < 0) {
        var_v0_3 = temp_a0_4 + 3;
    }
    ((S_80172D24_3 *)arg1)->unk_10 = temp_a0_4 - (var_v0_3 >> 2);
    temp_v0 = ((S_80172D24_1 *)arg0)->unk_9B + 1;
    goto store_state;

state_2:
    temp_v0_base = (s16 *)&D_8006CCD8;
    temp_a0_2 = temp_s4 * 2;
    temp_a0_3 = (s16 *)((u8 *)&D_8006CCE8 + temp_a0_2);
    ((S_80172D24_3 *)arg1)->unk_0C -=
        *(s16 *)((u8 *)temp_v0_base + temp_a0_2) << 16;
    ((S_80172D24_3 *)arg1)->unk_10 -= *temp_a0_3 << 16;

    if (((S_80172D24_1 *)arg0)->unk_96.u > 0) {
        ((S_80172D24_1 *)arg0)->unk_96.s--;
    } else if (((S_80172D24_2 *)arg2)->unk_14 & 0x6000) {
        ((S_80172D24_1 *)arg0)->unk_96.s = 0;
    }
    if (((S_80172D24_1 *)arg0)->unk_96.u != 0) {
        return;
    }
    if (((S_80172D24_0 *)arg3)->unk_28 != 0) {
        var_v1 = 8;
        goto increment_state;
    }

start_action:
    ((S_80172D24_3 *)arg1)->unk_14 = 0;
    ((S_80172D24_3 *)arg1)->unk_10 = 0;
    ((S_80172D24_3 *)arg1)->unk_0C = 0;
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
        ax = ((S_80172D24_2 *)arg2)->unk_24 << 6;
        dy = ((S_80172D24_3 *)arg1)->unk_02 - 0x20;
        ((S_80172D24_3 *)arg1)->unk_0C = ((ax - dy) << 15) / temp_a0;

        ax2 = ((S_80172D24_2 *)arg2)->unk_25 << 6;
        dy2 = ((S_80172D24_3 *)arg1)->unk_06 - 0x20;
        ((S_80172D24_3 *)arg1)->unk_10 =
            ((ax2 - dy2) << 15) / ((S_80172D24_1 *)arg0)->unk_96.u;
    }

    temp_v0 = ((S_80172D24_1 *)arg0)->unk_96.s - 1;
    ((S_80172D24_1 *)arg0)->unk_96.s = temp_v0;
    if ((temp_v0 << 16) > 0) {
        return;
    }

    ((S_80172D24_3 *)arg1)->unk_14 = 0;
    ((S_80172D24_3 *)arg1)->unk_10 = 0;
    ((S_80172D24_3 *)arg1)->unk_0C = 0;
    func_800A2B04(arg1, ((S_80172D24_2 *)arg2)->unk_24, ((S_80172D24_2 *)arg2)->unk_25);

    global = &D_80083460;
    value = *(s32 *)((u8 *)global + 0x10);
    if (value == (s32)((u8 *)arg3 - 0x20)) {
        *(s32 *)((u8 *)global + 0x10) = value & 0x7FFFFFFF;
    }
    ((S_80172D24_1 *)arg0)->unk_8C = &D_80170E68;
}
