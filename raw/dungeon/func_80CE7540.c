#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern s32 D_800814A0[3];

void func_80170D40(void *arg0, void *arg1, void *arg2)
{
    u16 temp_v0;
    u8 temp_v1;

    FIELD(arg0, u8, 2) = (u8)(FIELD(arg0, u8, 2) - 0x40);
    temp_v1 = FIELD(arg0, u8, 0) - 0x40;
    FIELD(arg0, u8, 0) = temp_v1;
    FIELD(arg0, u8, 1) = (u8)(FIELD(arg0, u8, 1) - 0x40);
    FIELD(arg2, u8, 0xC) = temp_v1;
    FIELD(arg2, u8, 0xD) = FIELD(arg0, u8, 1);
    FIELD(arg2, u8, 0xE) = FIELD(arg0, u8, 2);
    temp_v0 = FIELD(arg0, u16, 0x18) - 1;
    FIELD(arg0, u16, 0x18) = temp_v0;
    if ((temp_v0 << 0x10) <= 0) {
        FIELD(arg0, u16, -2) = (u16)(FIELD(arg0, u16, -2) | 0x8000);
        D_800814A0[0] = (s32)(D_800814A0[0] | 0x8000);
    }
}
