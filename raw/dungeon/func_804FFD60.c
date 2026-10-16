#include "common.h"
#include "m2c_compat.h"

extern M2C_UNK D_800E2970;

void func_80017560(void) {
    M2C_UNK *var_v0;
    s32 var_v1;

    var_v0 = &D_800E2970;
    var_v1 = 0x24;
    do {
        M2C_FIELD(var_v0, s16 *, 0xC) = 0;
        var_v1 -= 1;
        var_v0 += 0x14;
    } while (var_v1 > 0);
}
