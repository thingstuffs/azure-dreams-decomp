#include "common.h"
extern s32 *D_80701968;
void func_80701858(s32 arg0) {
    s32 *temp_v1;
    s32 temp_v0;
    s32 var_v0;

    if (arg0 != 1) {
        var_v0 = arg0;
        if (arg0 < 0) {
            var_v0 = arg0 + 0x1F;
        }
        temp_v0 = var_v0 >> 5;
        temp_v1 = D_80701968 + temp_v0;
        *temp_v1 &= ~(1 << (arg0 - (temp_v0 << 5)));
    }
}
