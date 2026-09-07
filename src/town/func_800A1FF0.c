#include "common.h"

s32 func_8009F750(s32 arg0, s32 arg1, s32 arg2) {
    s32 var_v1;

    var_v1 = 0;
    if (arg2 > 0) {
loop_1:
        if (arg0 == arg1) {
            return var_v1;
        }
        var_v1 += 1;
        if (var_v1 < arg2) {
            arg1 += 4;
            goto loop_1;
        }
    }
    return -1;
}
