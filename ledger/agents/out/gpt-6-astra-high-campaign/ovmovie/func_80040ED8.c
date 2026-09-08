#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8005FFFC();                            /* extern */
M2C_UNK func_801779A0();                         /* extern */

/* Apply the requested mode, performing setup when it is zero. */
void func_80040ED8(s32 mode) {
    if (mode == 0) {
        func_8005FFFC();
    }
    func_801779A0(mode);
}
