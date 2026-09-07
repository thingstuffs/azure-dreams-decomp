#include "common.h"

void func_800B7384(s16 *arg0) {
    s16 *var_a0;
    s16 temp_v0;
    s16 temp_v0_2;
    s16 var_a1;
    s16 var_v1;

    var_a0 = arg0;
    var_a1 = 0;
    do {
        var_v1 = 0;
loop_2:
        *var_a0 = 0;
        temp_v0_2 = var_v1 + 1;
        var_v1 = temp_v0_2;
        var_a0 += 1;
        if (temp_v0_2 < 0x80) {
            goto loop_2;
        }
        temp_v0 = var_a1 + 1;
        var_a1 = temp_v0;
    } while (temp_v0 < 0x80);
}
