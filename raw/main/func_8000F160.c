#include "common.h"

extern s32 D_80083E98[];

s32 func_80022160(void) {
    s32 *var_v1;
    register s32 var_a0 ASM_REG("$4");
    register s32 var_a1 ASM_REG("$5");

    var_a1 = 0;
    var_a0 = var_a1;
    var_v1 = D_80083E98;
    while (var_a0 < 5) {
        if (*var_v1 != 0) {
            var_a1 += 1;
        }
        var_a0 += 1;
        var_v1 += 0x20;
    }
    return var_a1;
}
