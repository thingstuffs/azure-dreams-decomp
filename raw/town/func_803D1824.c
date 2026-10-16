#include "common.h"
#include "m2c_compat.h"

s32 func_80018824(s32 arg0, s32 arg1) {
    s32 var_v1;

    var_v1 = 0;
    if (arg1 > 0) {
        do {
            *(arg0 + var_v1) = 0;
            var_v1 += 1;
        } while (var_v1 < arg1);
    }
    return arg0;
}
