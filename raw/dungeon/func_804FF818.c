#include "common.h"
#include "m2c_compat.h"

extern M2C_UNK D_800E3DA0;

void func_80017018(void) {
    s32 var_v1;
    s8 *temp_v0;

    var_v1 = 6;
    do {
        temp_v0 = var_v1 + &D_800E3DA0;
        var_v1 -= 1;
        *temp_v0 = 0;
    } while (var_v1 >= 0);
}
