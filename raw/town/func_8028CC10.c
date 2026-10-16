#include "common.h"
#include "m2c_compat.h"

s32 func_80019C68();                                /* extern */

s32 func_80017410(void *arg0) {
    s32 temp_v0;

    temp_v0 = func_80019C68();
    if (temp_v0 == 0) {
        M2C_FIELD(arg0, s32 *, -0x1C) = (s32) (M2C_FIELD(arg0, s32 *, -0x1C) | 0x8000);
    }
    return temp_v0;
}
