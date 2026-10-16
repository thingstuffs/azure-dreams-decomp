#include "common.h"
#include "m2c_compat.h"

s32 func_80016CF8(s16);                             /* extern */

s32 func_80016598(void *arg0) {
    s32 var_v0;

    var_v0 = 0;
    if (func_80016CF8(*(s16 *)0x8001607E) == 0) {
        var_v0 = func_80016CF8(M2C_FIELD(arg0, s16 *, 0x18)) != 0;
    }
    return var_v0;
}
