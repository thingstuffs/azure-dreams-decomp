#include "common.h"

s32 func_8003FC64();                         /* extern */

s32 func_800B12F4(void) {
    s32 temp_v0;
    s32 var_v1;

    temp_v0 = func_8003FC64(0);
    var_v1 = 0;
    if (temp_v0 != 0) {
        var_v1 = temp_v0 + 0x20;
    }
    return var_v1;
}
