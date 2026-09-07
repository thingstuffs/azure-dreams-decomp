#include "common.h"
#include "m2c_compat.h"

s32 func_800B3C04();                                /* extern */
M2C_UNK func_800B3D04();                    /* extern */

void func_800B3D84(s32 arg0) {
    s32 temp_v0;

    temp_v0 = func_800B3C04();
    if (temp_v0 != -1) {
        func_800B3D04(arg0, temp_v0);
    }
}
