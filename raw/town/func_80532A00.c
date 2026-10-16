#include "common.h"
#include "m2c_compat.h"

s32 func_80016250(s32);                             /* extern */
extern s32 D_8001967C;
extern M2C_UNK D_80019700;

s32 func_80016A00(s32 arg2) {
    s32 var_v1;

    var_v1 = 0;
    if (arg2 == 8) {
        var_v1 = func_80016250(*((D_8001967C * 4) + &D_80019700));
    }
    return var_v1;
}
