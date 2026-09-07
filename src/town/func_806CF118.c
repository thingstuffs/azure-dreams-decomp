#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80016ABC(); /* extern */
s32 func_80017434();                                /* extern */
extern u8 D_80017570;
extern M2C_UNK D_80017658;

void func_806CF118(s32 arg0, M2C_UNK arg1, M2C_UNK arg2) {
    s32 var_a0;
    s32 temp_v0;

    temp_v0 = func_80017434();
    var_a0 = temp_v0;
    if (temp_v0 < 0) {
        var_a0 = temp_v0 + 3;
    }
    func_80016ABC(((temp_v0 - ((var_a0 >> 2) * 4)) * 8) + &D_80017570, &D_80017658, arg0, arg2);
}
