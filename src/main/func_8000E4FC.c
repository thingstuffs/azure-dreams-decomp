#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80021538();                            /* extern */
extern s32 D_800287E4;

s32 func_800214FC(void) {
    s32 var_s0;

    var_s0 = 0;
    if (D_800287E4 != 0) {
        var_s0 = D_800287E4;
        func_80021538();
    }
    return var_s0;
}
