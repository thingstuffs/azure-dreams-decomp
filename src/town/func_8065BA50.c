#include "common.h"
#include "m2c_compat.h"

s32 func_800173CC();                    /* extern */
s32 func_80017FEC();                                /* extern */

s32 func_80016250(s32 arg0, M2C_UNK arg1) {
    s32 var_v0;

    var_v0 = 0;
    if (func_80017FEC() >= 2) {
        var_v0 = func_800173CC(arg0, arg1) != 0;
    }
    return var_v0;
}
