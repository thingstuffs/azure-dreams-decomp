#include "common.h"
#include "m2c_compat.h"

extern s16 D_800EA000;

void func_8001744C(void) {
    s16 *var_v0;
    s16 *var_v1;
    s32 var_a0;

    var_v0 = &D_800EA000;
    var_a0 = 0x1000;
    var_v1 = &D_800EA000 + 2;
    do {
        var_a0 -= 1;
        *var_v0 = 0;
        M2C_FIELD(var_v1, s16 *, 2) = 0;
        M2C_FIELD(var_v1, s16 *, 0) = 0;
        var_v1 += 6;
        var_v0 += 6;
    } while (var_a0 > 0);
}
