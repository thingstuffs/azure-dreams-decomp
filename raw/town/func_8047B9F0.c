#include "common.h"
#include "m2c_compat.h"

s32 func_800198D0(s16);                             /* extern */
extern s32 D_80019BB4;

s32 func_800181F0(void) {
    s32 var_a0;

    var_a0 = 0;
    if (D_80019BB4 != 6) {
        var_a0 = func_800198D0(*(s16 *)0x800164BC) != 0;
    }
    return var_a0;
}
