#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8016E334(void *, s32, s32, M2C_UNK);   /* extern */

s32 func_8016E89C(void *arg0, s32 arg1, s32 arg2) {
    s32 var_a1;
    s32 var_a2;
    void *temp_a2;
    void *var_a0;
    void *var_s0;

    var_a1 = arg1;
    var_a2 = arg2;
    var_s0 = arg0;
    var_a0 = var_s0;
loop_1:
    func_8016E334(var_a0, var_a1, var_a2, 0);
    temp_a2 = M2C_FIELD(var_s0, void **, -8);
    var_s0 = temp_a2 + 0x20;
    if (temp_a2 != NULL) {
        var_a1 = M2C_FIELD(temp_a2, s32 *, 8);
        var_a2 = M2C_FIELD(temp_a2, s32 *, 0xC);
        var_a0 = var_s0;
        goto loop_1;
    }
    return 0;
}
