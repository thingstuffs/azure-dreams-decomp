#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

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

    temp_s4 = (FIELD(arg3, u16, 0x6A) >> 9) & 7;
    state = FIELD(arg0, u8, 0x9B);

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
    if (FIELD(arg3, u8, 0x28) == 0) {
        goto start_action;
    }
    if (FIELD(arg2, u16, 0x14) & 0x8000) {
        FIELD(arg0, u16, 0x96) = 0;
        FIELD(arg0, u8, 0x9B) = 3;
        return;
    }
    FIELD(arg0, u16, 0x96) = 12;
    FIELD(arg0, u8, 0x9B)++;

state_1:
    temp_v0 = FIELD(arg0, u16, 0x96) - 1;
    FIELD(arg0, u16, 0x96) = temp_v0;
    if ((temp_v0 << 16) != 0) {
        return;
    }

    FIELD(arg2, void *, 0x2C) = D_80173874;
    func_80047784(arg2,
        D_80173874[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
        0);

    temp_v0_base = (s16 *)&D_8006CCD8;
    temp_v1_2 = temp_s4 * 2;
    FIELD(arg1, s32, 0xC) =
        *(s16 *)((u8 *)temp_v0_base + temp_v1_2) << 19;
    FIELD(arg1, s32, 0x10) =
        *(s16 *)((u8 *)&D_8006CCE8 + temp_v1_2) << 19;

    var_v1 = -1;
    if (FIELD(arg3, s32, 0x1C) & 0x228) {
        var_v1 = 8;
    }
    FIELD(arg0, u16, 0x96) = var_v1;

    temp_v1_3 = FIELD(arg1, s32, 0xC);
    var_v0_2 = temp_v1_3;
    if (temp_v1_3 < 0) {
        var_v0_2 = temp_v1_3 + 3;
    }
    temp_a0_4 = FIELD(arg1, s32, 0x10);
    FIELD(arg1, s32, 0xC) = temp_v1_3 - (var_v0_2 >> 2);
    var_v0_3 = temp_a0_4;
    if (temp_a0_4 < 0) {
        var_v0_3 = temp_a0_4 + 3;
    }
    FIELD(arg1, s32, 0x10) = temp_a0_4 - (var_v0_3 >> 2);
    temp_v0 = FIELD(arg0, u8, 0x9B) + 1;
    goto store_state;

state_2:
    temp_v0_base = (s16 *)&D_8006CCD8;
    temp_a0_2 = temp_s4 * 2;
    temp_a0_3 = (s16 *)((u8 *)&D_8006CCE8 + temp_a0_2);
    FIELD(arg1, s32, 0xC) -=
        *(s16 *)((u8 *)temp_v0_base + temp_a0_2) << 16;
    FIELD(arg1, s32, 0x10) -= *temp_a0_3 << 16;

    if (FIELD(arg0, s16, 0x96) > 0) {
        FIELD(arg0, u16, 0x96)--;
    } else if (FIELD(arg2, u16, 0x14) & 0x6000) {
        FIELD(arg0, u16, 0x96) = 0;
    }
    if (FIELD(arg0, s16, 0x96) != 0) {
        return;
    }
    if (FIELD(arg3, u8, 0x28) != 0) {
        var_v1 = 8;
        goto increment_state;
    }

start_action:
    FIELD(arg1, s32, 0x14) = 0;
    FIELD(arg1, s32, 0x10) = 0;
    FIELD(arg1, s32, 0xC) = 0;
    func_800AAA54(arg0, arg1, arg2, D_80173874);
    return;

increment_state:
    temp_v0 = FIELD(arg0, u8, 0x9B) + 1;
    FIELD(arg0, u16, 0x96) = var_v1;

store_state:
    FIELD(arg0, u8, 0x9B) = temp_v0;
    return;

state_3:
    temp_a0 = FIELD(arg0, s16, 0x96);
    if (temp_a0 != 0) {
        ax = FIELD(arg2, u8, 0x24) << 6;
        dy = FIELD(arg1, s16, 2) - 0x20;
        FIELD(arg1, s32, 0xC) = ((ax - dy) << 15) / temp_a0;

        ax2 = FIELD(arg2, u8, 0x25) << 6;
        dy2 = FIELD(arg1, s16, 6) - 0x20;
        FIELD(arg1, s32, 0x10) =
            ((ax2 - dy2) << 15) / FIELD(arg0, s16, 0x96);
    }

    temp_v0 = FIELD(arg0, u16, 0x96) - 1;
    FIELD(arg0, u16, 0x96) = temp_v0;
    if ((temp_v0 << 16) > 0) {
        return;
    }

    FIELD(arg1, s32, 0x14) = 0;
    FIELD(arg1, s32, 0x10) = 0;
    FIELD(arg1, s32, 0xC) = 0;
    func_800A2B04(arg1, FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25));

    global = &D_80083460;
    value = *(s32 *)((u8 *)global + 0x10);
    if (value == (s32)((u8 *)arg3 - 0x20)) {
        *(s32 *)((u8 *)global + 0x10) = value & 0x7FFFFFFF;
    }
    FIELD(arg0, void *, 0x8C) = &D_80170E68;
}
