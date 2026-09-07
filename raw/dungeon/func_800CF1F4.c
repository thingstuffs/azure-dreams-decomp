#include "common.h"

#define FIELD(expr, type, offset) (*(type *)((s8 *)(expr) + (offset)))

extern s32 func_80042900(void *, s32);
extern s32 D_800814A0[3];

void func_800D4954(void *arg0, void *arg1, void *arg2) {
    u16 temp_v0;
    void *temp_a0;
    void *temp_s1;
    void *temp_v1;

    temp_a0 = FIELD(arg0, void *, 0x88);
    temp_v1 = FIELD(temp_a0, void *, -0x18);
    temp_s1 = temp_a0 - 0x20;
    FIELD(arg1, u16, 2) = FIELD(temp_v1, u16, 2);
    FIELD(arg1, u16, 6) = FIELD(temp_v1, u16, 6);
    FIELD(arg1, s16, 0xA) = FIELD(temp_v1, u16, 0xA) - 0x32;
    FIELD(arg2, s8, 0xE) = 0x28;
    FIELD(arg2, s8, 0xD) = 0x28;
    FIELD(arg2, s8, 0xC) = 0x28;
    FIELD(arg2, u16, 0x1A) = FIELD(arg2, u16, 0x1A) + 0x190;
    if (FIELD(arg0, u16, 0x5A) & 1) {
        FIELD(arg2, s8, 0xC) = 0x64;
    }
    if (FIELD(arg0, u16, 0x5A) & 2) {
        FIELD(arg2, s8, 0xD) = 0x64;
    }
    if (FIELD(arg0, u16, 0x5A) & 4) {
        FIELD(arg2, s8, 0xE) = 0x64;
    }
    if (FIELD(arg2, u16, 0x1C) < 0x1800U) {
        temp_v0 = FIELD(arg2, u16, 0x1E) + 0x190;
        FIELD(arg2, u16, 0x1E) = temp_v0;
        FIELD(arg2, u16, 0x1C) = temp_v0;
    }
    if ((func_80042900(temp_a0, 0x1D) << 0x10) == 0) {
        FIELD(arg0, u16, -2) |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }
    if (FIELD(temp_s1, u16, 0x1E) & 0x8000) {
        FIELD(arg0, u16, -2) |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }
}
