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

    direction = (FIELD(arg3, u16, 0x6A) >> 9) & 7;

    switch (FIELD(arg0, u8, 0x9B)) {
    case 0:
        func_800AD4D0(arg3);
        temp_v0_base = (s16 *)&D_8006CCD8;
        temp_v1_2 = direction * 2;
        FIELD(arg1, s32, 0xC) =
            *(s16 *)((u8 *)temp_v0_base + temp_v1_2) << 0x12;
        FIELD(arg1, s32, 0x10) =
            *(s16 *)((u8 *)&D_8006CCE8 + temp_v1_2) << 0x12;
        FIELD(arg0, u8, 0x9B)++;

        if (FIELD(arg3, u8, 0x28) == 0) {
            goto start_action;
        }
        if (FIELD(arg2, u16, 0x14) & 0x8000) {
            FIELD(arg0, s16, 0x96) = 0;
            FIELD(arg0, u8, 0x9B) = 2;
            return;
        }

        timer = -1;
        if (FIELD(arg3, s32, 0x1C) & 0x228) {
            timer = 8;
        }
        FIELD(arg0, s16, 0x96) = timer;

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
        /* fall through */

    case 1:
        temp_v0_base = (s16 *)&D_8006CCD8;
        temp_a0_3 = direction * 2;
        temp_a0_4 = (s16 *)((u8 *)&D_8006CCE8 + temp_a0_3);
        FIELD(arg1, s32, 0xC) -=
            *(s16 *)((u8 *)temp_v0_base + temp_a0_3) << 0xF;
        FIELD(arg1, s32, 0x10) -= *temp_a0_4 << 0xF;

        if (FIELD(arg0, s16, 0x96) > 0) {
            FIELD(arg0, s16, 0x96) = FIELD(arg0, u16, 0x96) - 1;
        } else if (FIELD(arg2, u16, 0x14) & 0x6000) {
            FIELD(arg0, s16, 0x96) = 0;
        }
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
        func_800AAA54(arg0, arg1, arg2, &D_80173D24);
        return;

increment_state:
        FIELD(arg0, s16, 0x96) = 4;
        FIELD(arg0, u8, 0x9B)++;
        return;

    case 2:
        if (FIELD(arg0, s16, 0x96) != 0) {
            ax = FIELD(arg2, u8, 0x24) << 6;
            dy = FIELD(arg1, s16, 2) - 0x20;
            FIELD(arg1, s32, 0xC) = (ax - dy) << 0x10 >> 1;
            ax2 = FIELD(arg2, u8, 0x25) << 6;
            dy2 = FIELD(arg1, s16, 6) - 0x20;
            FIELD(arg1, s32, 0x10) = (ax2 - dy2) << 0x10 >> 1;
        }

        timer = FIELD(arg0, u16, 0x96) - 1;
        FIELD(arg0, s16, 0x96) = timer;
        if ((s32)(timer << 16) > 0) {
            return;
        }

        FIELD(arg1, s32, 0x14) = 0;
        FIELD(arg1, s32, 0x10) = 0;
        FIELD(arg1, s32, 0xC) = 0;
        func_800A2B04(arg1, FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25));

        FIELD(arg2, void *, 0x2C) = D_80173D0C;
        func_80047784(arg2,
            D_80173D0C[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
            0);

        state = &D_80083460;
        value = state[4];
        if (value == (s32)((u8 *)arg3 - 0x20)) {
            state[4] = value & 0x7FFFFFFF;
        }
        FIELD(arg0, void *, 0x8C) = D_80170E5C;
        return;

    default:
        return;
    }
}
