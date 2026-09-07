#include "common.h"

s32 func_800AD968(void) {
    volatile s32 *var_v1;
    s32 var_a0;

    var_v1 = (volatile s32 *)0x8001029C;
    var_a0 = 0;
    if (var_v1[0] != 0) {
        do {
            var_v1 = var_v1 + 1;
            var_a0++;
        } while (var_v1[0] != 0);
    }
    return var_a0;
}
