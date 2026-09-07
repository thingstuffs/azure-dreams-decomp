#include "common.h"

s32 func_80033B2C();                             /* extern */
extern s16 D_80028010[8];

s32 func_80025E54(void) {
    s16 *var_s1;
    s32 var_s0;
    s32 var_s2;
    s32 var_s3;

    var_s2 = 0;
    var_s0 = 0;
    var_s3 = 1;
    var_s1 = D_80028010;
    do {
        if (func_80033B2C(*var_s1) != 0) {
            var_s2 += var_s3 << var_s0;
        }
        var_s0 += 1;
        var_s1 += 1;
    } while (var_s0 < 8);
    return var_s2;
}
