#include "common.h"
#include "m2c_compat.h"

extern M2C_UNK D_800E3548;

void func_8001E96C(void) {
    s32 *var_v0;
    s32 var_v1;

    var_v1 = 0x3F;
    var_v0 = &D_800E3548 + 0xFC;
    do {
        *var_v0 = 0;
        var_v1 -= 1;
        var_v0 -= 4;
    } while (var_v1 >= 0);
}
