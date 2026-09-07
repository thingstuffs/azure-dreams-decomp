#include "common.h"
#include "m2c_compat.h"

#include "common.h"

M2C_UNK func_800253A0(); /* extern */
M2C_UNK func_8003F320();                            /* extern */
M2C_UNK func_8004B634();                            /* extern */

void func_8004B660(s32 arg0, M2C_UNK arg1, M2C_UNK arg2) {
    func_8004B634();
    func_8003F320();
    func_800253A0(arg0, arg1, 1, arg2);
}
