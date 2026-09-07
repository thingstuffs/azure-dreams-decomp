#include "common.h"

s32 func_800198D0();                             /* extern */
extern s16 D_80016480;
extern s32 D_80019BB4;

s32 func_80477130(void) {
    s32 var_a0;

    var_a0 = 0;
    if (D_80019BB4 != 1) {
        var_a0 = func_800198D0(D_80016480) != 0;
    }
    return var_a0;
}
