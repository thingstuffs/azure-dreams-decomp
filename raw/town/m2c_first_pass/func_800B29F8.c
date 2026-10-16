#include "common.h"
#include "m2c_compat.h"

void func_800B0158(s32 arg0) {
    (M2C_UNK (*)())0x800B0134();
    (M2C_UNK (*)(s32, s32, s32))0x800AFF00(arg0 + 0x98, arg0 + 0x70, arg0 + 0x80);
    (M2C_UNK (*)(s32))0x800B0024(arg0);
}
