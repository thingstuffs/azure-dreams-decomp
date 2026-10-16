#include "common.h"
#include "m2c_compat.h"

void func_800B3868(s32 arg0) {
    (M2C_UNK (*)())0x800B384C();
    (M2C_UNK (*)(s32, s32, s32))0x800B3688(arg0 + 0x98, arg0 + 0x70, arg0 + 0x80);
    (M2C_UNK (*)(s32))0x800B3734(arg0);
}
