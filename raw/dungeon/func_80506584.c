#include "common.h"
#include "m2c_compat.h"

extern s16 D_80083350;
extern M2C_UNK D_800EA000;

s16 func_8001DD84(s32 arg0, s32 arg1, s32 arg2, s16 arg3, s16 arg4) {
    s32 var_a0;
    s32 var_a1;
    s32 var_a2;
    u16 var_t1;
    void *temp_t0;

    var_a2 = arg2 - 1;
    var_a0 = arg0 + arg3;
    var_t1 = M2C_FIELD(((((arg1 << D_80083350) + arg0) * 6) + &D_800EA000), u16 *, 2);
    var_a1 = arg1 + arg4;
    if (var_a2 > 0) {
        do {
            temp_t0 = (((var_a1 << D_80083350) + var_a0) * 6) + &D_800EA000;
            if (M2C_FIELD(temp_t0, s16 *, 2) < (s16) var_t1) {
                var_t1 = (u16) M2C_FIELD(temp_t0, s16 *, 2);
            }
            var_a0 += arg3;
            var_a2 -= 1;
            var_a1 += arg4;
        } while (var_a2 > 0);
    }
    return (s16) var_t1;
}
