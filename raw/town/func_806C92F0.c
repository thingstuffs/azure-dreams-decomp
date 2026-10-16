#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80016A78(s32);                         /* extern */
M2C_UNK func_80016B20(s32, M2C_UNK);                /* extern */
s32 func_800175BC(M2C_UNK);                         /* extern */

void func_800162F0(s32 arg0, M2C_UNK arg1) {
    if (func_800175BC(0x3EC) != 0) {
        func_80016A78(arg0);
    }
    func_80016B20(arg0, arg1);
}
