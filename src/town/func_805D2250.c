#include "common.h"
#include "m2c_compat.h"

s32 func_800191E8(M2C_UNK *);                                /* extern */
extern M2C_UNK D_8001AA2E;

M2C_UNK *func_805D2250(M2C_UNK *arg0) {
    M2C_UNK *var_s0;

    var_s0 = arg0;
    if (func_800191E8(arg0) < -0x2F) {
        var_s0 = &D_8001AA2E;
    }
    return var_s0;
}
