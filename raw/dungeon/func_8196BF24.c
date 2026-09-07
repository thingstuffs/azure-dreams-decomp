#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern s32 D_800814A0[3];

void func_8196BF24(void *arg0, s32 arg1, void *arg2) {
    u8 temp_v0;

    FIELD(arg0, u16, 0x2C) = (s16)(FIELD(arg0, u16, 0x2C) - 1);
    FIELD(arg2, u16, 0x1C) = (u16)(FIELD(arg2, u16, 0x1C) - 0x300);
    FIELD(arg2, u16, 0x1E) = (u16)(FIELD(arg2, u16, 0x1E) - 0x200);
    temp_v0 = FIELD(arg0, u8, 0x40) - 0x18;
    FIELD(arg0, u8, 0x40) = temp_v0;
    if ((temp_v0 & 0xFF) == 0xE8) {
        FIELD(arg0, u8, 0x40) = 0x18U;
        FIELD(arg0, u8, 0x41) = (u8)(FIELD(arg0, u8, 0x41) - 0x20);
    }
    if (FIELD(arg0, s16, 0x2C) <= 0) {
        FIELD(arg0, u16, -2) = (u16)(FIELD(arg0, u16, -2) | 0x8000);
        D_800814A0[0] = (s32)(D_800814A0[0] | 0x8000);
    }
}
