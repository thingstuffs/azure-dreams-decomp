#include "common.h"
#include "m2c_compat.h"

void func_8016B384(void *arg0, void *arg1, void *arg2) {
    s16 temp_v0;
    s32 temp_lo;
    u32 temp_a3;
    u32 temp_v1;

    temp_a3 = M2C_FIELD(arg1, u32 *, 0x10);
    M2C_FIELD(arg1, s32 *, 0) = (s32) (M2C_FIELD(arg1, s32 *, 0) + M2C_FIELD(arg1, u32 *, 0xC));
    M2C_FIELD(arg1, s32 *, 4) = (s32) (M2C_FIELD(arg1, s32 *, 4) + temp_a3);
    temp_v1 = M2C_FIELD(arg1, u32 *, 0xC);
    M2C_FIELD(arg1, s32 *, 8) = (s32) (M2C_FIELD(arg1, s32 *, 8) + M2C_FIELD(arg1, s32 *, 0x14));
    M2C_FIELD(arg1, u32 *, 0xC) = (u32) ((s32) (temp_v1 + (temp_v1 >> 0x1F)) >> 1);
    M2C_FIELD(arg1, u32 *, 0x10) = (u32) ((s32) (temp_a3 + (temp_a3 >> 0x1F)) >> 1);
    M2C_FIELD(arg1, s32 *, 0x14) = (s32) ((s32) M2C_FIELD(arg1, s32 *, 0x14) / 2);
    temp_lo = (s32) (M2C_FIELD(arg0, s16 *, 0xC) << 7) / (s16) M2C_FIELD(arg0, s16 *, 0xE);
    M2C_FIELD(arg2, s8 *, 0xE) = (s8) temp_lo;
    M2C_FIELD(arg2, s8 *, 0xD) = (s8) temp_lo;
    M2C_FIELD(arg2, s8 *, 0xC) = (s8) temp_lo;
    temp_v0 = (u16) M2C_FIELD(arg0, s16 *, 0xC) - 1;
    M2C_FIELD(arg0, s16 *, 0xC) = temp_v0;
    if ((temp_v0 << 0x10) <= 0) {
        M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
        *(s32 *)0x800814A0 |= 0x8000;
    }
}
