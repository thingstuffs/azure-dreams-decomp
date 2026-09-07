#include "common.h"
#include "m2c_compat.h"

extern s32 D_800834B8;
extern M2C_UNK D_80097D2C;
extern s32 D_800CFCC4;

s32 func_800C2AB4(s32 arg0) {
    s32 var_v1;

    var_v1 = 0;
    if (D_800CFCC4 == arg0) {
        var_v1 = D_800834B8 == (s32) &D_80097D2C;
    }
    return var_v1;
}
