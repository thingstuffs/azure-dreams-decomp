#include "common.h"
#include "m2c_compat.h"

s32 func_800C9034(void *arg0, s32 arg1, void *arg2) {
    s32 var_a1;
    void *temp_a2;
    void *var_a2;
    void *var_s0;

    var_a1 = arg1;
    var_a2 = arg2;
    var_s0 = arg0;
loop_1:
    (M2C_UNK (*)(void *, s32, void *, s16))0x800C9088(var_s0, var_a1, var_a2, M2C_FIELD(var_a2, s16 *, 6));
    temp_a2 = M2C_FIELD(var_s0, void **, -8);
    var_s0 = temp_a2 + 0x20;
    if (temp_a2 != NULL) {
        var_a1 = M2C_FIELD(temp_a2, s32 *, 8);
        var_a2 = M2C_FIELD(temp_a2, void **, 0xC);
        goto loop_1;
    }
    return 0;
}
