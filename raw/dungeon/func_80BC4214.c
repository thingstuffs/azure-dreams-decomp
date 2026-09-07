#include "common.h"

extern void func_800A2B04();
extern void func_800AAA54();
extern void func_800AD4D0();

extern s32 D_80083460;
extern s32 D_801719DC;
extern s32 D_8017466C;

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

void func_80173A14(void *arg0, void *arg1, void *arg2, void *arg3)
{
    s16 timer;
    s32 value;
    s32 *state;

    switch (FIELD(arg0, u8, 0x9B)) {
    case 0:
        func_800AD4D0(arg3);
        FIELD(arg1, s32, 0x10) = 0;
        FIELD(arg1, s32, 0x0C) = 0;
        FIELD(arg0, u8, 0x9B)++;

        if (FIELD(arg3, u8, 0x28) == 0) {
            goto start_action;
        }
        if (FIELD(arg2, u16, 0x14) & 0x8000) {
            FIELD(arg0, s16, 0x96) = 0;
            FIELD(arg0, u8, 0x9B) = 2;
            return;
        }
        if (FIELD(arg3, s32, 0x1C) & 0x228) {
            timer = 8;
        } else {
            timer = -1;
        }
        FIELD(arg0, s16, 0x96) = timer;
        /* fall through */

    case 1:
        FIELD(arg1, s32, 0x10) = 0;
        FIELD(arg1, s32, 0x0C) = 0;
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
        goto start_action;

start_action:
        FIELD(arg1, s32, 0x14) = 0;
        FIELD(arg1, s32, 0x10) = 0;
        FIELD(arg1, s32, 0x0C) = 0;
        func_800AAA54(arg0, arg1, arg2, &D_8017466C);
        return;

increment_state:
        FIELD(arg0, s16, 0x96) = 2;
        FIELD(arg0, u8, 0x9B)++;
        return;

    case 2:
        if (FIELD(arg0, s16, 0x96) != 0) {
            FIELD(arg1, s32, 0x10) = 0;
            FIELD(arg1, s32, 0x0C) = 0;
        }
        timer = FIELD(arg0, u16, 0x96) - 1;
        FIELD(arg0, s16, 0x96) = timer;
        if ((s32)(timer << 16) > 0) {
            return;
        }
        FIELD(arg1, s32, 0x14) = 0;
        FIELD(arg1, s32, 0x10) = 0;
        FIELD(arg1, s32, 0x0C) = 0;
        func_800A2B04(arg1, FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25));

        state = &D_80083460;
        value = state[4];
        if (value == (s32)((u8 *)arg3 - 0x20)) {
            state[4] = value & 0x7FFFFFFF;
        }
        FIELD(arg0, void *, 0x8C) = &D_801719DC;
        return;

    default:
        return;
    }
}
