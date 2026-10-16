#include "common.h"
#include "m2c_compat.h"

u8 *func_800188B4(u8 *arg0, u8 *arg1) {
    u8 *temp_v1;
    u8 *var_a0;
    u8 *var_a0_2;
    u8 *var_a1;

    var_a0 = arg0;
    var_a1 = arg1;
    temp_v1 = var_a0;
    if (*temp_v1 != 0) {
        var_a0_2 = var_a0 + 1;
        do {
            var_a0_2 += 1;
        } while (*var_a0_2 != 0);
        var_a0 = var_a0_2 - 1;
    }
loop_5:
    if (*var_a1 != 0) {
        *var_a0 = *var_a1;
        var_a0 += 1;
        var_a1 += 1;
        goto loop_5;
    }
    *var_a0 = 0;
    return temp_v1;
}
