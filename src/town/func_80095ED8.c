#include "common.h"
#include "m2c_compat.h"

s32 func_800352FC(s32, M2C_UNK, M2C_UNK, s32);                                /* extern */
M2C_UNK func_80093D48();       /* extern */

void func_80093638(s32 arg0, M2C_UNK arg1, M2C_UNK arg2, s32 arg3) {
    if (func_800352FC(arg0, arg1, arg2, arg3) == 0) {
        func_80093D48(arg0, arg1, arg2);
    }
}
