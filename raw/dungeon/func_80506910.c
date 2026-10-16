#include "common.h"
#include "m2c_compat.h"

extern M2C_UNK D_800E3548;
extern M2C_UNK D_800E36C8;

s32 func_8001E110(s32 arg0, s16 arg1, s16 arg2) {
    M2C_UNK *var_t0;
    M2C_UNK *var_v1;
    s32 var_a3;
    s32 var_v0;

    var_a3 = 0;
    var_v1 = &D_800E36C8;
    var_t0 = &D_800E3548;
loop_1:
    if ((arg0 == var_a3) || (M2C_FIELD(var_t0, u8 *, 1) == 0) || (M2C_FIELD(var_v1, u8 *, 0) != arg1) || (var_v0 = 1, (M2C_FIELD(var_v1, u8 *, 1) != arg2))) {
        var_v1 += 0xC;
        var_a3 += 1;
        var_t0 += 4;
        if (var_a3 >= 0x40) {
            var_v0 = 0;
        } else {
            goto loop_1;
        }
    }
    return var_v0;
}
