#include "common.h"

s32 func_800B2214(s32 *arg0, s32 arg1, s32 arg2) {
    s32 *var_a0;
    s32 var_v1;

    var_a0 = arg0;
    var_v1 = 0;
    if (arg2 > 0) {
loop_1:
        if (arg1 != *var_a0) {
            var_v1 += 1;
            var_a0 += 1;
            if (var_v1 < arg2) {
                goto loop_1;
            }
        }
    }
    return var_v1;
}
