#include "common.h"
#include "m2c_compat.h"

s32 func_80018CA8(s32 arg0, s32 arg1) {
    s32 var_a3;
    s32 var_t0;
    void **var_a2;
    void *temp_v0;
    void *temp_v1;

    var_t0 = -1;
    temp_v0 = M2C_FIELD(*(void **)0x80016000, void **, 0x38);
    var_a2 = temp_v0 + 0x29C;
    var_a3 = 0;
    if (M2C_FIELD(temp_v0, s32 *, 0x29C) != 0) {
loop_1:
        temp_v1 = *var_a2;
        if ((M2C_FIELD(temp_v1, u8 *, 1) == arg0) && (M2C_FIELD(temp_v1, u8 *, 0) == arg1)) {
            var_t0 = var_a3;
        } else {
            var_a2 += 4;
            var_a3 += 1;
            if (*var_a2 != NULL) {
                goto loop_1;
            }
        }
    }
    return var_t0;
}
