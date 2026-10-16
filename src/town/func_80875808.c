#include "common.h"
extern s32 *D_80701968;
void func_80701808(s32 arg0) {
    s32 *temp_a0;
    s32 temp_v1;
    s32 var_v1;

    if (arg0 != 0) {
        var_v1 = arg0;
        if (arg0 < 0) {
            var_v1 = arg0 + 0x1F;
        }
        temp_v1 = var_v1 >> 5;
        temp_a0 = D_80701968 + temp_v1;
        *temp_a0 |= 1 << (arg0 - (temp_v1 << 5));
    }
}
