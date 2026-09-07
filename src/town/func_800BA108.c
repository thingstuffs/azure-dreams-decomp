#include "common.h"

extern u16 D_80162004[];

void func_800B7868(s16 arg0, s16 arg1, u16 *arg2) {
    s16 temp_v0;
    s16 temp_v0_2;
    s16 var_t2;
    s16 var_a1;
    u16 temp_t3;
    u16 temp_t4;
    u16 temp_v1;

    temp_t4 = *arg2++;
    temp_t3 = *arg2++;
    var_t2 = 0;
    while ((var_t2 << 0x10) < (temp_t3 << 0x10)) {
        var_a1 = 0;
        while (var_a1 < (s16) temp_t4) {
            temp_v1 = *arg2;
            if (temp_v1 != 0) {
                D_80162004[((var_t2 + arg1) << 7) + var_a1 + arg0] = temp_v1;
            }
            temp_v0_2 = var_a1 + 1;
            var_a1 = temp_v0_2;
            arg2++;
        }
        temp_v0 = var_t2 + 1;
        var_t2 = temp_v0;
    }
}
