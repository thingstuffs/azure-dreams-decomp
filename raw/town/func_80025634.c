#include "common.h"
#include "m2c_compat.h"

u32 func_800C2D94(s32 arg0) {
    s32 var_v0;

    var_v0 = (*(s16 *)0x80083228 - (arg0 - 0x500)) & 0xFFF;
    if (var_v0 < 0) {
        var_v0 += 0x1FF;
    }
    return (u32) var_v0 >> 9;
}
