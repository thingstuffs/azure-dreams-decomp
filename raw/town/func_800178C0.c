#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8004E99C(s32);                         /* extern */

void func_800B5020(s32 arg0) {
    s32 **var_s0;
    s32 **var_s0_2;
    s32 var_s1;
    s32 var_s1_2;

    var_s1 = 0x10;
    var_s0 = arg0 + 0x40;
    do {
        var_s1 += 1;
        func_8004E99C(**var_s0);
        **var_s0 = 0;
        var_s0 += 4;
    } while (var_s1 < 0x1A);
    var_s1_2 = 0x1A;
    var_s0_2 = arg0 + 0x68;
    do {
        var_s1_2 += 1;
        func_8004E99C(**var_s0_2);
        **var_s0_2 = 0;
        var_s0_2 += 4;
    } while (var_s1_2 < 0x24);
}
