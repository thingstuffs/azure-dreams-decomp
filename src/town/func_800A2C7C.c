#include "common.h"

extern s32 D_80100AA0[];

void func_800A03DC(void) {
    s32 *var_v0;
    s32 var_v1;

    var_v1 = 19;
    var_v0 = D_80100AA0;
    var_v0 += 19;
    do {
        *var_v0 = 0;
        var_v1--;
        var_v0--;
    } while (var_v1 >= 0);
}
