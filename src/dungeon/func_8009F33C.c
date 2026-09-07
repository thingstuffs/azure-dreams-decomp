#include "common.h"
#include "m2c_compat.h"

typedef struct S_800A4A9C_0 {
    u8 pad_00[0x2C];
    s8 unk_2C;
} S_800A4A9C_0;   /* var_a0 in func_800A4A9C */

s32 func_800A4A9C(s32 arg0) {
    s32 var_v1;
    void *var_a0;

    var_v1 = 3;
    var_a0 = arg0 + 6;
loop_1:
    if (((S_800A4A9C_0 *)var_a0)->unk_2C != 0) {
        var_v1 -= 1;
        var_a0 -= 2;
        if (var_v1 < 0) {
            return 0;
        } else {
            goto loop_1;
        }
    }
    return 1;
}
