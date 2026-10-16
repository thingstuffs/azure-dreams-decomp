#include "common.h"
#include "m2c_compat.h"

s32 func_8001A7B0(s32 arg0) {
    s32 var_v0;
    s32 var_v1;
    u8 *var_a1;

    var_a1 = M2C_FIELD(*(void **)0x80016000, s32 *, 0x38) + 0x33A4;
    var_v1 = 0;
loop_1:
    var_v0 = 1;
    if (*var_a1 != arg0) {
        var_v1 += 1;
        var_a1 += 2;
        if (var_v1 >= 0x22) {
            var_v0 = 0;
        } else {
            goto loop_1;
        }
    }
    return var_v0;
}
