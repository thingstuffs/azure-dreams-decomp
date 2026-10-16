#include "common.h"
#include "m2c_compat.h"

s32 *func_80018874(s32 *arg0, s32 arg1) {
    s32 *var_a0;

    var_a0 = arg0;
    if (M2C_FIELD(var_a0, s32 *, 4) != 0) {
loop_1:
        if (*var_a0 != arg1) {
            var_a0 += 8;
            if (M2C_FIELD(var_a0, s32 *, 4) != 0) {
                goto loop_1;
            }
        }
    }
    return var_a0;
}
