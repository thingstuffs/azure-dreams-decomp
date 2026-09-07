#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800B5174();                            /* extern */
M2C_UNK func_800B52F4();                /* extern */
M2C_UNK func_800B5774();                /* extern */
M2C_UNK func_800B59A4();                /* extern */

void func_800B5AC8(s32 arg0, M2C_UNK arg1) {
    func_800B5174();
    func_800B52F4(arg0, arg1);
    func_800B5774(arg0, arg1);
    func_800B59A4(arg0, arg1);
}
