#include "common.h"

extern s32 D_800287CC;
extern u8 D_80084120;

s32 func_80022138(void) {
    s32 *var_v0;

    var_v0 = &D_80084120;
    if (D_800287CC != 0) {
        var_v0 = &D_80084120 + 4;
    }
    return *var_v0;
}
