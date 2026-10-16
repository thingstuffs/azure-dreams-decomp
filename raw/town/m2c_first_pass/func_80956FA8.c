#include "common.h"
#include "m2c_compat.h"

void func_80023FA8(void *arg0, void *arg2) {
    u16 temp_v0;

    M2C_FIELD(arg2, s32 *, 0xC) = (s32) (M2C_FIELD(arg2, s32 *, 0xC) + 0xFFEFEFF0);
    if (M2C_FIELD(arg0, s16 *, 8) != 0) {
        temp_v0 = (M2C_FIELD(arg2, u16 *, 0x1E) + 0x120) - ((u8) M2C_FIELD(arg2, s32 *, 0xC) >> 3);
        M2C_FIELD(arg2, u16 *, 0x1E) = temp_v0;
        M2C_FIELD(arg2, u16 *, 0x1C) = temp_v0;
    }
    if ((u8) M2C_FIELD(arg2, s32 *, 0xC) == 0) {
        M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
        *(s32 *)0x800814A0 |= 0x8000;
    }
}
