#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800453E0(void *, s32, void *, s16);    /* extern */
extern s16 D_8015191C;

s32 func_8014FE08(void *arg0, s32 arg1, void *arg2) {
    s32 var_a1;
    void *temp_a2;
    void *var_a2;
    void *var_s0;

    var_a1 = arg1;
    var_a2 = arg2;
    var_s0 = arg0;
loop_1:
    *(s32 *)0x1F80013C = (s32) D_8015191C;
    if (!(M2C_FIELD(var_a2, u16 *, 0x14) & 0x80)) {
        func_800453E0(var_s0, var_a1, var_a2, M2C_FIELD(var_a2, s16 *, 6));
    }
    temp_a2 = M2C_FIELD(var_s0, void **, -8);
    var_s0 = temp_a2 + 0x20;
    if (temp_a2 != NULL) {
        var_a1 = M2C_FIELD(temp_a2, s32 *, 8);
        var_a2 = M2C_FIELD(temp_a2, void **, 0xC);
        goto loop_1;
    }
    return 0;
}
