#include "common.h"
#include "m2c_compat.h"

s32 func_800176B8(s32, s32, s32, s32);                                /* extern */
M2C_UNK func_80018594();                     /* extern */
M2C_UNK func_800188E8();   /* extern */

s32 func_80016B50(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 temp_v0;

    temp_v0 = func_800176B8(arg0, arg1, arg2, arg3);
    if (temp_v0 != 0) {
        func_80018594(0x146E);
        func_800188E8(0x990, 3, 2);
    }
    return temp_v0;
}
