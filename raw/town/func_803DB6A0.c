#include "common.h"
#include "m2c_compat.h"

extern M2C_UNK D_80016470;
extern M2C_UNK D_800167B4;
extern M2C_UNK D_80016818;

void func_80017EA0(s32 arg0) {
    void *temp_a0;

    M2C_FIELD(&D_800167B4, s32 *, 0x20) = (s32) *((arg0 * 0xC) + &D_80016470);
    temp_a0 = (arg0 * 4) + &D_80016818;
    M2C_FIELD(&D_800167B4, u16 *, 0x24) = (u16) M2C_FIELD(temp_a0, u16 *, 0);
    M2C_FIELD(&D_800167B4, u16 *, 0x26) = (u16) M2C_FIELD(temp_a0, u16 *, 2);
}
