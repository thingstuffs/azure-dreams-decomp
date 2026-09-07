#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
s32 func_8008AD1C(arg0, arg1, arg2);                                /* extern */
M2C_UNK func_8008AE4C();                         /* extern */
s32 func_8008AFB0();      /* extern */

void func_8008B0E8(s32 arg0, M2C_UNK arg1, M2C_UNK arg2) {
    s32 var_v0;

    var_v0 = func_8008AD1C(arg0, arg1, arg2);
    if (var_v0 < 0) {
        var_v0 = func_8008AFB0(arg0, arg1, arg2, var_v0 & 0x7FFFFFFF);
    }
    if (var_v0 != 0) {
        func_8008AE4C(var_v0);
    }
}
