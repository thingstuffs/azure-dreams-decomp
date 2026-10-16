#include "common.h"
#include "m2c_compat.h"

void func_801561A4(void *arg0) {
    s32 temp_a0;
    s32 temp_v1;
    u16 temp_v1_2;

    temp_v1 = M2C_FIELD(arg0, s32 *, 0x10);
    temp_a0 = M2C_FIELD(arg0, s32 *, 0x14);
    M2C_FIELD(arg0, s32 *, 0xC) = (s32) (M2C_FIELD(arg0, s32 *, 0xC) + temp_v1);
    M2C_FIELD(arg0, s32 *, 0x10) = (s32) (temp_v1 + temp_a0);
    M2C_FIELD(arg0, s32 *, 0x14) = (s32) (temp_a0 + 0xFFFF4000);
    temp_v1_2 = M2C_FIELD(arg0, u16 *, 0x18) - 1;
    M2C_FIELD(arg0, u16 *, 0x18) = temp_v1_2;
    M2C_FIELD(arg0, s32 *, 8) = (s32) (M2C_FIELD(arg0, s32 *, 8) + 0x10000);
    if ((temp_v1_2 << 0x10) <= 0) {
        M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
        *(s32 *)0x800814A0 |= 0x8000;
    }
}
