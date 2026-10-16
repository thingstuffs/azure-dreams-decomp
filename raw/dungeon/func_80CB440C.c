#include "common.h"
#include "m2c_compat.h"

void func_80155C0C(void *arg0, void *arg2) {
    s16 temp_v0;

    M2C_FIELD(arg2, u16 *, 0x1A) = (u16) (M2C_FIELD(arg2, u16 *, 0x1A) + 0x320);
    M2C_FIELD(arg2, s8 *, 0xC) = (s8) ((M2C_FIELD(arg0, u8 *, 0) * M2C_FIELD(arg0, s16 *, 0x24)) / 5);
    M2C_FIELD(arg2, s8 *, 0xD) = (s8) ((M2C_FIELD(arg0, u8 *, 1) * M2C_FIELD(arg0, s16 *, 0x24)) / 5);
    M2C_FIELD(arg2, s8 *, 0xE) = (s8) ((M2C_FIELD(arg0, u8 *, 2) * M2C_FIELD(arg0, s16 *, 0x24)) / 5);
    temp_v0 = (u16) M2C_FIELD(arg0, s16 *, 0x24) - 1;
    M2C_FIELD(arg0, s16 *, 0x24) = temp_v0;
    if ((temp_v0 << 0x10) <= 0) {
        M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
        *(s32 *)0x800814A0 |= 0x8000;
    }
}
