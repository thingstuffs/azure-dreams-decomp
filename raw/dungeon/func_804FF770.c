#include "common.h"
#include "m2c_compat.h"

extern s8 D_800E3DB0;

void func_80016F70(void) {
    s16 temp_v0;
    s16 temp_v0_2;
    s16 var_a2;
    s16 var_a2_2;
    s8 *var_a0;
    s8 *var_v1;
    s8 *var_v1_2;
    s8 var_a1;

    var_a0 = &D_800E3DB0;
    var_a2 = 0;
    var_a1 = 0;
    var_v1 = &D_800E3DB0 + 3;
    do {
        temp_v0 = var_a2 + 1;
        var_a2 = temp_v0;
        *var_a0 = 1;
        M2C_FIELD(var_v1, s8 *, 0) = var_a1;
        var_a1 += 1;
        M2C_FIELD(var_v1, s8 *, -2) = 0;
        M2C_FIELD(var_v1, s8 *, -1) = 0;
        var_v1 += 8;
        var_a0 += 8;
    } while (temp_v0 < 4);
    var_a2_2 = 0;
    var_v1_2 = var_a0 + 3;
    do {
        temp_v0_2 = var_a2_2 + 1;
        var_a2_2 = temp_v0_2;
        *var_a0 = 3;
        M2C_FIELD(var_v1_2, s8 *, 0) = var_a1;
        var_a1 += 1;
        M2C_FIELD(var_v1_2, s8 *, -2) = 0;
        M2C_FIELD(var_v1_2, s8 *, -1) = 0;
        var_v1_2 += 8;
        var_a0 += 8;
    } while (temp_v0_2 < 2);
    M2C_FIELD(var_a0, s8 *, 0) = 2;
    M2C_FIELD(var_a0, s8 *, 1) = 0;
    M2C_FIELD(var_a0, s8 *, 2) = 0;
    M2C_FIELD(var_a0, s8 *, 3) = var_a1;
    M2C_FIELD(var_a0, s32 *, 4) = 0;
}
