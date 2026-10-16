#include "common.h"
#include "m2c_compat.h"

void func_8015EEF4(void *arg0, void *arg2) {
    s8 temp_v1;
    u16 temp_v0;
    u16 temp_v0_2;

    temp_v0 = M2C_FIELD(arg2, u16 *, 0x1E) + 0x78;
    M2C_FIELD(arg2, u16 *, 0x1E) = temp_v0;
    M2C_FIELD(arg2, u16 *, 0x1C) = temp_v0;
    M2C_FIELD(arg2, u16 *, 0x1A) = (u16) (M2C_FIELD(arg2, u16 *, 0x1A) + 0x2BC);
    temp_v0_2 = M2C_FIELD(arg0, u16 *, 0x18) - 1;
    M2C_FIELD(arg0, u16 *, 0x18) = temp_v0_2;
    if ((s16) temp_v0_2 < 0xC) {
        temp_v1 = ((s16) temp_v0_2 << 7) / 12;
        M2C_FIELD(arg2, s8 *, 0xE) = temp_v1;
        M2C_FIELD(arg2, s8 *, 0xD) = temp_v1;
        M2C_FIELD(arg2, s8 *, 0xC) = temp_v1;
    }
    if ((s16) M2C_FIELD(arg0, u16 *, 0x18) <= 0) {
        M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
        *(s32 *)0x800814A0 |= 0x8000;
    }
}
