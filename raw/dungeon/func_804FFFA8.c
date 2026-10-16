#include "common.h"
#include "m2c_compat.h"

extern M2C_UNK D_800E2970;

void func_800177A8(void) {
    s32 var_v1;
    void *var_v0;

    var_v1 = 0x23;
    var_v0 = &D_800E2970 + 0x2BC;
    do {
        M2C_FIELD(var_v0, s16 *, 0xA) = 0;
        M2C_FIELD(var_v0, s16 *, 0xE) = 0;
        M2C_FIELD(var_v0, s32 *, 0x10) = 0;
        var_v1 -= 1;
        var_v0 -= 0x14;
    } while (var_v1 >= 0);
}
