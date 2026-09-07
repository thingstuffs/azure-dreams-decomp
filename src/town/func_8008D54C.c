#include "common.h"

void func_8008ACAC(s32 arg0, s32 arg1, s32 arg2) {
    s32 *var_a0;
    s32 *var_a1;
    s32 temp_v0;
    s32 var_a2;
    s32 var_a2_2;

    var_a2 = arg2;
    var_a0 = arg0 + var_a2;
    var_a1 = arg1 + var_a2;
    if (var_a2 < 0) {
        var_a2 += 3;
    }
    var_a2_2 = var_a2 >> 2;
    if (var_a2_2 > 0) {
        do {
            temp_v0 = *var_a1;
            var_a1 -= 1;
            var_a2_2 -= 1;
            *var_a0 = temp_v0;
            var_a0 -= 1;
        } while (var_a2_2 > 0);
    }
}
