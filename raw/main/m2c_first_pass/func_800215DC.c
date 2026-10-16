#include "common.h"
#include "m2c_compat.h"

void func_804085DC(s32 arg0) {
    *(s8 *)0x8008CA34 = 1;
    (M2C_UNK (*)())0x80400E34();
    (M2C_UNK (*)(s32, M2C_UNK))0x804083FC(arg0, 0);
}
