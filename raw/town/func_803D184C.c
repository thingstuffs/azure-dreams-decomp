#include "common.h"
#include "m2c_compat.h"

void func_8001884C(s32 *arg0, s32 *arg1, s32 arg2) {
    s32 *var_a0;
    s32 *var_a1;
    s32 var_a2;

    var_a0 = arg0;
    var_a1 = arg1;
    var_a2 = arg2;
    if (var_a2 != 0) {
        do {
            *var_a0 = *var_a1;
            var_a1 += 4;
            var_a2 -= 1;
            var_a0 += 4;
        } while (var_a2 != 0);
    }
}
