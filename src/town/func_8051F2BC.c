#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800160D4(s32);                            /* extern */
M2C_UNK func_80016104();     /* extern */
extern M2C_UNK D_80018E80;

void func_80016ABC(s32 arg0, M2C_UNK arg1, M2C_UNK arg2) {
    func_800160D4(arg0);
    func_80016104(&D_80018E80, arg0, arg2);
}
