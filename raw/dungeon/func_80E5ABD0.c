#include "common.h"
#include "m2c_compat.h"

void func_801583D0(void *arg0, void *arg1, void *arg2) {
    s32 temp_a1;
    u16 temp_v0;
    u8 temp_v0_2;
    u8 temp_v0_3;

    temp_v0 = M2C_FIELD(arg0, u16 *, 0x20) - 1;
    M2C_FIELD(arg0, u16 *, 0x20) = temp_v0;
    if ((s16) temp_v0 <= 0) {
        M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
        *(s32 *)0x800814A0 |= 0x8000;
        return;
    }
    temp_v0_2 = M2C_FIELD(arg2, u8 *, 0xC);
    temp_v0_3 = temp_v0_2 - ((s32) temp_v0_2 / (s16) temp_v0);
    M2C_FIELD(arg2, u8 *, 0xC) = temp_v0_3;
    M2C_FIELD(arg2, u8 *, 0xD) = temp_v0_3;
    M2C_FIELD(arg2, u8 *, 0xE) = temp_v0_3;
    temp_a1 = M2C_FIELD(arg1, s32 *, 0x14);
    M2C_FIELD(arg1, s32 *, 0) = (s32) (M2C_FIELD(arg1, s32 *, 0) + M2C_FIELD(arg1, s32 *, 0xC));
    M2C_FIELD(arg1, s32 *, 4) = (s32) (M2C_FIELD(arg1, s32 *, 4) + M2C_FIELD(arg1, s32 *, 0x10));
    M2C_FIELD(arg1, s32 *, 8) = (s32) (M2C_FIELD(arg1, s32 *, 8) + temp_a1);
    M2C_FIELD(arg1, s32 *, 0x14) = (s32) (temp_a1 + 0x60000);
}
