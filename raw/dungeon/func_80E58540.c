#include "common.h"
#include "m2c_compat.h"

void func_80155D40(void *arg0, void *arg2, void *arg3) {
    M2C_FIELD(arg0, s8 *, 0x9A) = 0x19;
    M2C_FIELD(arg0, s8 *, 0x9B) = 0;
    M2C_FIELD(arg0, s32 *, 0x8C) = 0;
    M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) & 0xF7FF);
    M2C_FIELD(arg0, s16 *, 0x96) = 0;
    M2C_FIELD(arg3, s32 *, 0x1C) = (s32) (M2C_FIELD(arg3, s32 *, 0x1C) | 0x10000000);
}
