#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern void func_800A2B04();
extern void func_800AAA54();
extern void func_800AD4D0();

extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern s32 D_80083460;
extern u8 D_801710F4[];
extern u8 D_80174F10[];

void func_80173420(void *arg0, void *arg1, void *arg2, void *arg3)
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

    temp_a0 = FIELD(arg0, u16, 0x96) - 1;
    temp_s4 = (FIELD(arg3, u16, 0x6A) >> 9) & 7;
    temp_v1 = FIELD(arg0, u8, 0x9B);
    FIELD(arg0, u16, 0x96) = temp_a0;
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
    FIELD(arg1, s32, 0xC) =
        *(s16 *)((u8 *)temp_v0_base + temp_v1_2) << 0x12;
    FIELD(arg1, s32, 0x10) =
        *(s16 *)((u8 *)&D_8006CCE8 + temp_v1_2) << 0x12;
    FIELD(arg0, u8, 0x9B)++;

    if (FIELD(arg3, u8, 0x28) == 0) {
        goto start_action;
    }
    if (FIELD(arg2, u16, 0x14) & 0x8000) {
        FIELD(arg0, u16, 0x96) = 0;
        FIELD(arg0, u8, 0x9B) = 2;
        return;
    }

    var_v1 = 6;
    if (FIELD(arg3, s32, 0x1C) & 0x228) {
        var_v1 = 8;
    }
    FIELD(arg0, u16, 0x96) = var_v1;

    temp_v1_3 = FIELD(arg1, s32, 0xC);
    var_v0 = temp_v1_3;
    if (temp_v1_3 < 0) {
        var_v0 = temp_v1_3 + 3;
    }
    temp_a0_2 = FIELD(arg1, s32, 0x10);
    FIELD(arg1, s32, 0xC) = temp_v1_3 - (var_v0 >> 2);
    var_v0_2 = temp_a0_2;
    if (temp_a0_2 < 0) {
        var_v0_2 = temp_a0_2 + 3;
    }
    FIELD(arg1, s32, 0x10) = temp_a0_2 - (var_v0_2 >> 2);

state_1:
    temp_v0_base = (s16 *)&D_8006CCD8;
    temp_a0_3 = temp_s4 * 2;
    temp_a0_4 = (s16 *)((u8 *)&D_8006CCE8 + temp_a0_3);
    FIELD(arg1, s32, 0xC) -=
        *(s16 *)((u8 *)temp_v0_base + temp_a0_3) << 0xE;
    FIELD(arg1, s32, 0x10) -= *temp_a0_4 << 0xE;

    if (FIELD(arg0, s16, 0x96) != 0) {
        return;
    }
    if (FIELD(arg3, u8, 0x28) != 0) {
        goto increment_state;
    }

start_action:
    FIELD(arg1, s32, 0x14) = 0;
    FIELD(arg1, s32, 0x10) = 0;
    FIELD(arg1, s32, 0xC) = 0;
    func_800AAA54(arg0, arg1, arg2, D_80174F10);
    return;

increment_state:
    FIELD(arg0, u16, 0x96) = 6;
    FIELD(arg0, u8, 0x9B)++;
    return;

state_2:
    if ((temp_a0 << 0x10) != 0) {
        ax = FIELD(arg2, u8, 0x24) << 6;
        dy = FIELD(arg1, s16, 2) - 0x20;
        FIELD(arg1, s32, 0xC) = (ax - dy) << 0x10 >> 1;
        ax2 = FIELD(arg2, u8, 0x25) << 6;
        dy2 = FIELD(arg1, s16, 6) - 0x20;
        FIELD(arg1, s32, 0x10) = (ax2 - dy2) << 0x10 >> 1;

        if (FIELD(arg0, s16, 0x96) > 0) {
            return;
        }
    }

    FIELD(arg1, s32, 0x14) = 0;
    FIELD(arg1, s32, 0x10) = 0;
    FIELD(arg1, s32, 0xC) = 0;
    func_800A2B04(arg1, FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25));

    state = &D_80083460;
    value = state[4];
    if (value == (s32)((u8 *)arg3 - 0x20)) {
        state[4] = value & 0x7FFFFFFF;
    }
    FIELD(arg0, void *, 0x8C) = D_801710F4;
}
