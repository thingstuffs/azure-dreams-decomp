#include "common.h"
#include "m2c_compat.h"

s32 func_80003C70(u16);                             /* extern */

s32 func_8000386C(void) {
    s32 var_v0;

    var_v0 = 0;
    if (func_80003C70(*(u16 *)0x3F5A) != 0) {
        var_v0 = (func_80003C70(0x1F9U) == 0) * 2;
    }
    return var_v0;
}
