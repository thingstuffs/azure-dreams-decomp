#include "common.h"

s32 *func_800196A8(s32 *arg0, s32 arg1) {
    s32 *var_a0;

    var_a0 = arg0;
    if (var_a0[1] != 0) {
loop_1:
        if (*var_a0 != arg1) {
            var_a0 += 2;
            if (var_a0[1] != 0) {
                goto loop_1;
            }
        }
    }
    return var_a0;
}
