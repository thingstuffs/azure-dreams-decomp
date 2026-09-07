#include "common.h"

s16 func_8008C6B8();

s16 func_8008CBF4(s32 arg0, s32 arg1, s32 arg2) {
    s16 temp_v0;
    s16 var_s1;
    s32 var_s0;

    var_s1 = 0;
    var_s0 = 0;
    if (arg2 > 0) {
        do {
            temp_v0 = func_8008C6B8(arg0, arg1, var_s0);
            if ((temp_v0 << 0x10) > (var_s1 << 0x10)) {
                var_s1 = temp_v0;
            }
            var_s0 += 1;
        } while (var_s0 < arg2);
    }
    return var_s1;
}
