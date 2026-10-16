#include "common.h"
#include "m2c_compat.h"

s32 func_80000C6C(s16);                             /* extern */

s32 func_800007E8(s32 arg0) {
    s16 *var_s0;

    var_s0 = M2C_FIELD((M2C_FIELD((arg0 * 4), u16 *, 0xF2A) * 4), s16 **, 0xF20);
loop_1:
    if (func_80000C6C(*var_s0) != 0) {
        var_s0 += 2;
        goto loop_1;
    }
    return *var_s0 == 0;
}
