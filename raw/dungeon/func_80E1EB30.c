#include "common.h"
#include "m2c_compat.h"

s32 func_800990FC();                                /* extern */
s32 func_80099194(M2C_UNK *, s32);                  /* extern */
M2C_UNK func_80099290(s32);                         /* extern */
s32 func_80099734(M2C_UNK, s32);                    /* extern */
M2C_UNK func_800A5720(s32);                         /* extern */
extern M2C_UNK D_800E1F7B;
extern M2C_UNK D_800E1F93;
extern M2C_UNK D_8016488C;

void func_8016A330(s32 arg0, M2C_UNK arg1) {
    M2C_UNK *var_a0;
    s32 temp_s1;
    s32 var_v0;

    temp_s1 = func_800990FC();
    if ((arg0 << 0x10) != 0) {
        var_v0 = func_80099734(arg1, temp_s1);
        var_a0 = &D_800E1F7B;
    } else {
        var_v0 = func_80099734(arg1, func_80099194(&D_800E1F93, temp_s1));
        var_a0 = &D_8016488C;
    }
    func_80099290(func_80099194(var_a0, var_v0));
    func_800A5720(temp_s1);
}
