#include "common.h"
#include "m2c_compat.h"

s32 func_800990FC();                                /* extern */
s32 func_80099194(M2C_UNK *, s32);                  /* extern */
M2C_UNK func_80099290(s32);                         /* extern */
s32 func_80099734(s32, s32);                        /* extern */
M2C_UNK func_800A5720(s32);                         /* extern */
extern M2C_UNK D_8016A440;
extern M2C_UNK D_8016A455;

void func_80169DA4(s32 arg0) {
    s32 temp_v0;

    temp_v0 = func_800990FC();
    func_80099290(func_80099194(&D_8016A455, func_80099734(arg0, func_80099194(&D_8016A440, temp_v0))));
    func_800A5720(temp_v0);
}
