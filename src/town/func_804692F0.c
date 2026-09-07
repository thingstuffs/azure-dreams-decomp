#include "common.h"

extern u8 D_8001791C[96];
s32 func_8001E670();

s32 func_8001A2F0(void) {
    s32 var_s2;
    s32 var_s1;
    u8 *var_s0;
    u8 *temp_v0;

    var_s2 = 0;
    var_s1 = 1;
    temp_v0 = D_8001791C;
    var_s0 = temp_v0 + 0xC;
    do {
        if (func_8001E670(*(s16 *)(var_s0 + 4)) != 0) {
            var_s2 += 1;
        }
        var_s1 += 1;
        var_s0 += 0xC;
    } while (var_s1 < 8);
    return var_s2;
}
