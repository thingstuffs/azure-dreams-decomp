#include "common.h"
#include "m2c_compat.h"

void func_80164BFC(void *arg0, void *arg1) {
    s16 temp_v0;
    u32 temp_a2;
    u32 temp_v1;

    temp_a2 = M2C_FIELD(arg1, u32 *, 0x10);
    M2C_FIELD(arg1, s32 *, 0) = (s32) (M2C_FIELD(arg1, s32 *, 0) + M2C_FIELD(arg1, u32 *, 0xC));
    M2C_FIELD(arg1, s32 *, 4) = (s32) (M2C_FIELD(arg1, s32 *, 4) + temp_a2);
    temp_v1 = M2C_FIELD(arg1, u32 *, 0xC);
    M2C_FIELD(arg1, s32 *, 8) = (s32) (M2C_FIELD(arg1, s32 *, 8) + M2C_FIELD(arg1, s32 *, 0x14));
    M2C_FIELD(arg1, u32 *, 0xC) = (u32) ((s32) (temp_v1 + (temp_v1 >> 0x1F)) >> 1);
    M2C_FIELD(arg1, u32 *, 0x10) = (u32) ((s32) (temp_a2 + (temp_a2 >> 0x1F)) >> 1);
    M2C_FIELD(arg1, s32 *, 0x14) = (s32) ((s32) M2C_FIELD(arg1, s32 *, 0x14) / 2);
    M2C_FIELD(arg0, s8 *, 4) = (s8) ((s32) (M2C_FIELD(arg0, u8 *, 0) * M2C_FIELD(arg0, s16 *, 0x32)) / (s16) M2C_FIELD(arg0, s16 *, 0x34));
    M2C_FIELD(arg0, s8 *, 5) = (s8) ((s32) (M2C_FIELD(arg0, u8 *, 1) * M2C_FIELD(arg0, s16 *, 0x32)) / (s16) M2C_FIELD(arg0, s16 *, 0x34));
    M2C_FIELD(arg0, s8 *, 6) = (s8) ((s32) (M2C_FIELD(arg0, u8 *, 2) * M2C_FIELD(arg0, s16 *, 0x32)) / (s16) M2C_FIELD(arg0, s16 *, 0x34));
    temp_v0 = (u16) M2C_FIELD(arg0, s16 *, 0x32) - 1;
    M2C_FIELD(arg0, s16 *, 0x32) = temp_v0;
    M2C_FIELD(arg0, s32 *, 8) = (s32) M2C_FIELD(arg0, s8 *, 4);
    if ((temp_v0 << 0x10) <= 0) {
        M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
        *(s32 *)0x800814A0 |= 0x8000;
    }
}
