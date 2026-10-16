#include "common.h"
#include "m2c_compat.h"

extern u16 D_80026472;
extern s32 D_800814A0;

void func_800248E4(void *arg0, void *arg2) {
    u8 temp_a0;
    u8 temp_v0;
    u8 temp_v1;

    D_80026472 += 1;
    temp_v0 = M2C_FIELD(arg2, u8 *, 0xC);
    temp_v1 = M2C_FIELD(arg2, u8 *, 0xD);
    M2C_FIELD(arg2, u8 *, 0xC) = (u8) (temp_v0 - (temp_v0 >> 3));
    temp_a0 = M2C_FIELD(arg2, u8 *, 0xE);
    M2C_FIELD(arg2, u8 *, 0xD) = (u8) (temp_v1 - (temp_v1 >> 3));
    M2C_FIELD(arg2, u8 *, 0xE) = (u8) (temp_a0 - (temp_a0 >> 3));
    if ((u8) M2C_FIELD(arg2, u8 *, 0xC) < 8U) {
        M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
        D_800814A0 |= 0x8000;
    }
}
