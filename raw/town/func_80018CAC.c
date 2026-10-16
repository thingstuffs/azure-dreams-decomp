#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800B5C60();                            /* extern */
M2C_UNK func_800B5D70(s32, M2C_UNK);                /* extern */
M2C_UNK func_800B5E28(s32, M2C_UNK);                /* extern */
M2C_UNK func_800B63EC(s32, M2C_UNK);                /* extern */

void func_800B640C(s32 arg0, M2C_UNK arg1) {
    func_800B5C60();
    func_800B5D70(arg0, arg1);
    func_800B5E28(arg0, arg1);
    func_800B63EC(arg0, arg1);
}
