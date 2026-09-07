#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8004B1A4();                         /* extern */
s32 func_8004B404();                         /* extern */
s32 func_800B0E18();                        /* extern */

s32 func_800B0F30(s32 arg0) {
    s32 temp_v0;
    s32 var_v0;

    temp_v0 = func_8004B404(0x100);
    var_v0 = temp_v0;
    if (temp_v0 != 0) {
        var_v0 = temp_v0;
        if (func_800B0E18(temp_v0, arg0) == 0) {
            func_8004B1A4(temp_v0);
            var_v0 = 0;
        }
    }
    return var_v0;
}
