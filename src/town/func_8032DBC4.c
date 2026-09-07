#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80019B54();                /* extern */
M2C_UNK func_80019BC0();                            /* extern */
M2C_UNK func_8001ACE8();                     /* extern */
s32 func_8001B0C8();                                /* extern */

void func_800183C4(s32 arg0, M2C_UNK arg1) {
    if (func_8001B0C8() >= 5) {
        func_80019BC0();
    }
    func_8001ACE8(0xD7F);
    func_80019B54(arg0, arg1);
}
