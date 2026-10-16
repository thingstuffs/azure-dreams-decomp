#include "common.h"
#include "m2c_compat.h"

void func_804057B0(s32 arg0) {
    (M2C_UNK (*)())0x804057A8();
    (M2C_UNK (*)(s32, s32, s32))0x80405624(arg0 + 0xAF8, arg0 + 0xAD0, arg0 + 0xAE0);
    (M2C_UNK (*)(s32))0x8040553C(arg0);
}
