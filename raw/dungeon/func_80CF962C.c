#include "common.h"
#include "m2c_compat.h"

void func_8015EE2C(void *arg0, void *arg2) {
    s16 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u16 *, 0x18) - 1;
    M2C_FIELD(arg0, u16 *, 0x18) = (u16) temp_v1;
    M2C_FIELD(arg2, s8 *, 0xC) = (s8) ((s32) (M2C_FIELD(arg0, u8 *, 0) * temp_v1) / (s16) M2C_FIELD(arg0, s16 *, 0x1A));
    M2C_FIELD(arg2, s8 *, 0xD) = (s8) ((s32) (M2C_FIELD(arg0, u8 *, 1) * (s16) M2C_FIELD(arg0, u16 *, 0x18)) / (s16) M2C_FIELD(arg0, s16 *, 0x1A));
    M2C_FIELD(arg2, s8 *, 0xE) = (s8) ((s32) (M2C_FIELD(arg0, u8 *, 2) * (s16) M2C_FIELD(arg0, u16 *, 0x18)) / (s16) M2C_FIELD(arg0, s16 *, 0x1A));
    if ((s16) M2C_FIELD(arg0, u16 *, 0x18) <= 0) {
        M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
        *(s32 *)0x800814A0 |= 0x8000;
    }
}
