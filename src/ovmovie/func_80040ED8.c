#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8005FFFC();                            /* extern */
M2C_UNK func_801779A0();                         /* extern */

void func_80040ED8(s32 arg0) {
    if (arg0 == 0) {
        func_8005FFFC();
    }
    func_801779A0(arg0);
}
