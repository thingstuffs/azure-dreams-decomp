#include "common.h"

extern s32 D_80019BB0;

s32 func_80017D98(void) {
    s32 var_a0;

    var_a0 = 0;
    if (D_80019BB0 != 1) {
        var_a0 = D_80019BB0 != 5;
    }
    return var_a0;
}
