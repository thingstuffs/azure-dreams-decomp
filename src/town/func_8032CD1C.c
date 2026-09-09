#include "common.h"
#include "m2c_compat.h"

s32 func_80019B54(void *, s32);                                /* extern */
M2C_UNK func_8001B168();   /* extern */

s32 func_8001751C(void *arg0, s32 arg1) {
    s32 temp_v0;

    temp_v0 = func_80019B54(arg0, arg1);
    if (temp_v0 != 0) {
        func_8001B168(0xD6E, 3, 2);
    }
    return temp_v0;
}
