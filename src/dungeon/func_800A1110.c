#include "common.h"

s32 func_800A6D30();                             /* extern */

s32 func_800A6870(s16 arg0) {
    s16 var_s0;

    var_s0 = arg0;
    if (arg0 == 0xFF) {
        var_s0 = 0x1E;
    }
    return ((s32) (var_s0 << 0x10) >> 0x12) + (func_800A6D30(arg0) & 3);
}
