#include "common.h"
#include "m2c_compat.h"

s32 func_800198D0(s16);                             /* extern */
extern s32 D_80019BB4;

s32 func_80018170(void) {
    s32 var_a0;

    var_a0 = 0;
    if (D_80019BB4 != 2) {
        var_a0 = func_800198D0(*(s16 *)0x8001648C) != 0;
    }
    return var_a0;
}
