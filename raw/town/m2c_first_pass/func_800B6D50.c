#include "common.h"
#include "m2c_compat.h"

void func_800B44B0(s32 arg0) {
    (M2C_UNK (*)())0x800B4494();
    (M2C_UNK (*)(s32, s32, s32))0x800B3EEC(arg0 + 0x4C, arg0 + 0x24, arg0 + 0x34);
    (M2C_UNK (*)(s32))0x800B43E8(arg0);
}
