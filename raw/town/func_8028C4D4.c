#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80019B54(s32, M2C_UNK);                /* extern */
M2C_UNK func_80019BC0(s32);                         /* extern */
s32 func_8001B0C8();                                /* extern */

void func_80016CD4(s32 arg0, M2C_UNK arg1) {
    if (func_8001B0C8() >= 0x14) {
        func_80019BC0(arg0);
    }
    func_80019B54(arg0, arg1);
}
