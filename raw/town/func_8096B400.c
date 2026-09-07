#include "common.h"

extern s32 *D_80129728[];
extern s32 D_801331A0;

void func_80123898(void) {
    s32 **base_v0;
    s32 **var_v1;
    s32 *temp_v0;
    s32 *var_a0;
    s32 var_a1;

    var_a1 = 0x10;
    var_a0 = &D_801331A0;
    base_v0 = D_80129728;
    var_v1 = base_v0 + 0x10;
    do {
        var_a1 += 1;
        *var_a0 = **var_v1;
        temp_v0 = *var_v1;
        var_v1 += 1;
        *temp_v0 = 0;
        var_a0 += 1;
    } while (var_a1 < 0x1C);
}
