#include "common.h"

s32 func_800B29A4(s32 *arg0) {
    s32 *var_a0;
    s32 var_v1;

    var_a0 = arg0;
    var_v1 = 0;
    if (*var_a0 != 0) {
        do {
            var_a0 += 1;
            var_v1 += 1;
        } while (*var_a0 != 0);
    }
    return var_v1;
}
