#include "common.h"

s32 func_800B555C(s32 arg0, s32 arg1) {
    s32 var_v1;

    var_v1 = 0;
    if (arg0 != arg1) {
        var_v1 = 3;
        if (arg0 < arg1) {
            var_v1 = 4;
        }
    }
    return var_v1;
}
