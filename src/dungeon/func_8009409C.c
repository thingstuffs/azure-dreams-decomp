#include "common.h"
#include "m2c_compat.h"

s32 func_800990FC(s32, s32, s32, s32);                                /* extern */
s32 func_80099194();                        /* extern */
M2C_UNK func_80099290();                         /* extern */
M2C_UNK func_800A5720();                         /* extern */

void func_800997FC(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 temp_v0;

    temp_v0 = func_800990FC(arg0, arg1, arg2, arg3);
    func_80099290(func_80099194(arg0, temp_v0));
    func_800A5720(temp_v0);
}
