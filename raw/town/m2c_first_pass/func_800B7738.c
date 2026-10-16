#include "common.h"
#include "m2c_compat.h"

void func_800B4E98(s32 arg0) {
    (M2C_UNK (*)())0x800B4E7C();
    (M2C_UNK (*)(s32, s32, s32))0x800B4CBC(arg0 + 0x4C, arg0 + 0x24, arg0 + 0x34);
    (M2C_UNK (*)(s32))0x800B4D64(arg0);
}
