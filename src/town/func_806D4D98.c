#include "common.h"

typedef s32 M2C_UNK;

extern s32 func_8001839C(void);
extern M2C_UNK D_8001B3F2[3];
extern M2C_UNK D_8001B71A[3];

M2C_UNK *func_80016D98(s32 arg0) {
    M2C_UNK *var_s0;

    var_s0 = 0;
    if (func_8001839C() < -0x2F) {
        if (arg0 == 0xB) {
            var_s0 = &D_8001B3F2[0];
        } else if (arg0 == 0x1C) {
            var_s0 = &D_8001B71A[0];
        }
    }
    return var_s0;
}
