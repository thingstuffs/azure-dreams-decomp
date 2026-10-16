#include "common.h"
#include "m2c_compat.h"

s32 func_8001CE14(s16 arg0, s32 arg1, s16 arg2) {
    s32 var_v0;

    var_v0 = 0;
    if ((arg0 << 0x10) >= (arg1 << 0x10)) {
        var_v0 = arg2 >= arg0;
    }
    return var_v0;
}
