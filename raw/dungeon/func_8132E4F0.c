#include "common.h"

#define FIELD(expr, type, offset) (*(type *)((u8 *)(expr) + (offset)))

extern s32 D_800814A0[3];

void func_801654F0(void *arg0, void *arg1)
{
    u16 temp_v0;

    FIELD(arg1, s32, 0) = FIELD(arg1, s32, 0) + FIELD(arg1, s32, 0xC);
    FIELD(arg1, s32, 4) = FIELD(arg1, s32, 4) + FIELD(arg1, s32, 0x10);
    FIELD(arg1, s32, 8) = FIELD(arg1, s32, 8) + FIELD(arg1, s32, 0x14);
    FIELD(arg0, u8, 4) = FIELD(arg0, u8, 0);
    FIELD(arg0, u8, 5) = FIELD(arg0, u8, 1);
    FIELD(arg0, u8, 6) = FIELD(arg0, u8, 2);
    temp_v0 = FIELD(arg0, u16, 0x32) - 1;
    FIELD(arg0, u16, 0x32) = temp_v0;
    FIELD(arg0, s32, 8) = FIELD(arg0, s32, 4);
    if ((temp_v0 << 0x10) <= 0) {
        FIELD(arg0, u16, -2) |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }
}
