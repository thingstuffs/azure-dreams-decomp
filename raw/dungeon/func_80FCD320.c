#include "common.h"
#include "m2c_compat.h"

void func_8015CB20(void *arg0, void *arg2) {
    s16 temp_v0_2;
    s16 temp_v1;
    s8 temp_v0;

    temp_v1 = M2C_FIELD(arg0, s16 *, 0x96);
    if (temp_v1 < 0x10) {
        temp_v0 = temp_v1 * 3;
        M2C_FIELD(arg2, s8 *, 0xE) = temp_v0;
        M2C_FIELD(arg2, s8 *, 0xD) = temp_v0;
        M2C_FIELD(arg2, s8 *, 0xC) = temp_v0;
    } else {
        M2C_FIELD(arg2, s8 *, 0xC) = 0x808080;
    }
    temp_v0_2 = (u16) M2C_FIELD(arg0, s16 *, 0x96) - 1;
    M2C_FIELD(arg0, s16 *, 0x96) = temp_v0_2;
    if ((temp_v0_2 << 0x10) <= 0) {
        M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
        *(s32 *)0x800814A0 |= 0x8000;
    }
}
