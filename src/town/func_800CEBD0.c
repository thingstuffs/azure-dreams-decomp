#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800BBC1C();                     /* extern */
M2C_UNK func_800CC384();       /* extern */

void func_800CC330(s32 arg0, M2C_UNK arg1, M2C_UNK arg2) {
    func_800BBC1C(arg1);
    func_800CC384(arg0, arg1, arg2);
}
