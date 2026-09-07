#include "common.h"
#include "m2c_compat.h"

s32 func_800176B8();                                /* extern */
M2C_UNK func_80018594();                     /* extern */
M2C_UNK func_800188E8();   /* extern */

s32 func_80016B50(void) {
    s32 temp_v0;

    temp_v0 = func_800176B8();
    if (temp_v0 != 0) {
        func_80018594(0x146E);
        func_800188E8(0x990, 3, 2);
    }
    return temp_v0;
}
