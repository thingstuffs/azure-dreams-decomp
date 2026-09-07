#include "common.h"

extern u16 D_800269F8[];
extern s32 D_800814A0[];

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

void func_80024888(void *arg0, void *arg1, void *arg2) {
    s32 temp_a0;
    s32 temp_a3;
    u16 temp_v0_global;
    u8 temp_v0;
    u8 temp_v0_2;
    u16 temp_v0_3;

    temp_v0_global = D_800269F8[0];
    temp_a0 = FIELD(arg1, s32, 0xC);
    temp_a3 = FIELD(arg1, s32, 0x10);
    D_800269F8[0] = temp_v0_global + 1;
    FIELD(arg1, s32, 0) = FIELD(arg1, s32, 0) + temp_a0;
    FIELD(arg1, s32, 4) = FIELD(arg1, s32, 4) + temp_a3;
    FIELD(arg1, s32, 8) = FIELD(arg1, s32, 8) + FIELD(arg1, s32, 0x14);
    FIELD(arg1, s32, 0x14) = FIELD(arg1, s32, 0x14) + 0x2000;
    temp_v0 = FIELD(arg2, u8, 0xC);
    temp_v0_2 = temp_v0 - (temp_v0 >> 4);
    FIELD(arg2, u8, 0xC) = temp_v0_2;
    FIELD(arg2, u8, 0xD) = temp_v0_2;
    FIELD(arg2, u8, 0xE) = temp_v0_2;
    temp_v0_3 = FIELD(arg0, u16, 0x30) - 1;
    FIELD(arg0, u16, 0x30) = temp_v0_3;
    if ((temp_v0_3 << 0x10) <= 0) {
        FIELD(arg0, u16, -2) = FIELD(arg0, u16, -2) | 0x8000;
        D_800814A0[0] |= 0x8000;
    }
}
