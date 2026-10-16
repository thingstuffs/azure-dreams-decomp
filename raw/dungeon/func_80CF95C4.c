#include "common.h"
#include "m2c_compat.h"

void func_8015EDC4(void *arg0, void *arg2) {
    s32 temp_lo;
    u16 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u16 *, 0x96) - 1;
    temp_lo = (s32) ((s32) (temp_v1 << 0x10) >> 9) / (s16) M2C_FIELD(arg0, s16 *, 0x9E);
    M2C_FIELD(arg0, u16 *, 0x96) = temp_v1;
    M2C_FIELD(arg2, s8 *, 0xC) = (s8) temp_lo;
    M2C_FIELD(arg2, s8 *, 0xE) = (s8) temp_lo;
    M2C_FIELD(arg2, s8 *, 0xD) = (s8) temp_lo;
    if ((s16) M2C_FIELD(arg0, u16 *, 0x96) <= 0) {
        M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
        *(s32 *)0x800814A0 |= 0x8000;
    }
}
