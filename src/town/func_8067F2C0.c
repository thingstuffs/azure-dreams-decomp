#include "common.h"
#include "m2c_compat.h"

s32 func_80017978();                    /* extern */
s32 func_80018604();                                /* extern */

s32 func_8067F2C0(s32 arg0, M2C_UNK arg1) {
    s32 var_v0;

    var_v0 = 0;
    if (func_80018604() >= 0xA) {
        var_v0 = func_80017978(arg0, arg1) != 0;
    }
    return var_v0;
}
