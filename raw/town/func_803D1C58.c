#include "common.h"
#include "m2c_compat.h"

void func_80018C58(void) {
    s32 temp_a2;
    s32 temp_v1;
    s32 var_a0;
    s32 var_a1;
    s32 var_v0;

    var_a1 = 0;
    temp_a2 = M2C_FIELD(*(void **)0x80016000, s32 *, 0x38) + 0x29C;
    var_a0 = 0;
    var_v0 = 0 * 4;
loop_1:
    temp_v1 = *(var_v0 + temp_a2);
    if (temp_v1 != 0) {
        if (temp_v1 != -1) {
            if (var_a0 != var_a1) {
                *((var_a1 * 4) + temp_a2) = temp_v1;
            }
            var_a1 += 1;
        }
        var_a0 += 1;
        var_v0 = var_a0 * 4;
        if (var_a0 < 0x14) {
            goto loop_1;
        }
    }
    *((var_a1 * 4) + temp_a2) = 0;
}
