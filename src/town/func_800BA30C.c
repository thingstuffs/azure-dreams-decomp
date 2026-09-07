#include "common.h"

void func_800B7A6C(s32 arg0, s32 arg1, u16 *arg2, void *arg3) {
    register s16 var_a0;
    register s16 var_t1;
    u16 temp_t3;
    u16 temp_t4;
    u16 temp_v0;
    u16 temp_v1;

    temp_t4 = *arg2++;
    temp_t3 = *arg2++;
    temp_v1 = *arg2++;
    temp_v0 = *arg2++;
    var_t1 = 0;
    arg0 -= temp_v1;
    arg1 -= temp_v0;
    var_t1 = 0;
    while ((var_t1 << 0x10) < (temp_t3 << 0x10)) {
        var_a0 = 0;
        while (var_a0 < (s16) temp_t4) {
            temp_v1 = *arg2;
            if (temp_v1 != 0) {
                ((u16 *) arg3)[((var_t1 + (s16) arg1) << 7) + var_a0 + (s16) arg0] = temp_v1;
            }
            arg2++;
            var_a0++;
        }
        var_t1++;
    }
}
