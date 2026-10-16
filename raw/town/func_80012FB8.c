#include "common.h"
#include "m2c_compat.h"

s32 func_800B0718(void) {
    s32 *var_v1;
    s32 var_a0;

    var_v1 = (s32 *)0x8001029C;
    var_a0 = 0;
    if (*(s32 *)0x8001029C != 0) {
        do {
            var_v1 += 4;
            var_a0 += 1;
        } while (*var_v1 != 0);
    }
    return var_a0;
}
