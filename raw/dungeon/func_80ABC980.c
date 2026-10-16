#include "common.h"
#include "m2c_compat.h"

void func_80156180(void *arg0, void *arg2) {
    u16 temp_v0;

    temp_v0 = M2C_FIELD(arg2, u16 *, 0x1E) + 0x200;
    M2C_FIELD(arg2, u16 *, 0x1E) = temp_v0;
    M2C_FIELD(arg2, u16 *, 0x1C) = temp_v0;
    M2C_FIELD(arg2, u16 *, 0x1A) = (u16) (M2C_FIELD(arg2, u16 *, 0x1A) + 0x320);
    if ((u32) (temp_v0 & 0xFFFF) >= 0x2000U) {
        M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
        *(s32 *)0x800814A0 |= 0x8000;
    }
}
