#include "common.h"

extern s8 D_80129728;
extern s32 D_801331A0;

void func_801238E4(void) {
    s32 **var_a0;
    s32 *temp_v1;
    s32 *var_a1;
    s32 var_a2;
    s8 *temp_a0;

    var_a2 = 0x10;
    var_a1 = &D_801331A0;
    temp_a0 = &D_80129728;
    var_a0 = (s32 **)(temp_a0 + 0x40);
    do {
        temp_v1 = *var_a0;
        var_a0 += 1;
        var_a2 += 1;
        *temp_v1 = *var_a1;
        var_a1 += 1;
    } while (var_a2 < 0x1C);
}
