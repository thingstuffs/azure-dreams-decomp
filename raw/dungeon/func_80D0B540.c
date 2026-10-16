#include "common.h"
#include "m2c_compat.h"

void func_8014CD40(void *arg0, void *arg2) {
    u16 temp_v0;
    u8 temp_v1;

    M2C_FIELD(arg0, u8 *, 2) = (u8) (M2C_FIELD(arg0, u8 *, 2) - 0x40);
    temp_v1 = M2C_FIELD(arg0, u8 *, 0) - 0x40;
    M2C_FIELD(arg0, u8 *, 0) = temp_v1;
    M2C_FIELD(arg0, u8 *, 1) = (u8) (M2C_FIELD(arg0, u8 *, 1) - 0x40);
    M2C_FIELD(arg2, u8 *, 0xC) = temp_v1;
    M2C_FIELD(arg2, u8 *, 0xD) = (u8) M2C_FIELD(arg0, u8 *, 1);
    M2C_FIELD(arg2, u8 *, 0xE) = (u8) M2C_FIELD(arg0, u8 *, 2);
    temp_v0 = M2C_FIELD(arg0, u16 *, 0x18) - 1;
    M2C_FIELD(arg0, u16 *, 0x18) = temp_v0;
    if ((temp_v0 << 0x10) <= 0) {
        M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
        *(s32 *)0x800814A0 |= 0x8000;
    }
}
