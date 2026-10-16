#include "common.h"
#include "m2c_compat.h"

extern s32 D_00000E50;

void func_80000C44(s32 *arg0) {
    s32 *var_a2;
    s32 *var_a3;
    s32 temp_t0;

    var_a3 = &D_00000E50;
    var_a2 = arg0;
    temp_t0 = var_a2 + 0x30;
    do {
        M2C_FIELD(var_a3, s32 *, 0) = M2C_FIELD(var_a2, s32 *, 0);
        M2C_FIELD(var_a3, s32 *, 4) = (s32) M2C_FIELD(var_a2, s32 *, 4);
        M2C_FIELD(var_a3, s32 *, 8) = (s32) M2C_FIELD(var_a2, s32 *, 8);
        M2C_FIELD(var_a3, s32 *, 0xC) = (s32) M2C_FIELD(var_a2, s32 *, 0xC);
        var_a2 += 0x10;
        var_a3 += 0x10;
    } while (var_a2 != temp_t0);
    *var_a3 = *var_a2;
}
