#include "common.h"

extern s32 D_800FE508[4];

s32 func_80096E08(s32 *arg0, s32 *arg1)
{
    register s32 x ASM_REG("$7");
    register s32 y ASM_REG("$6");
    s32 x_bound;
    s32 y_bound;
    register s32 result ASM_REG("$3");

    x = *arg0;
    x_bound = D_800FE508[0];
    result = 0;
    if (x < x_bound) {
        *arg0 = x_bound;
        result = 0x10;
    } else {
        x_bound = D_800FE508[1];
        if (x_bound < x) {
            *arg0 = x_bound;
            result = 1;
            ASM_KEEP(x);
        }
    }

    y = *arg1;
    y_bound = D_800FE508[2];
    if (y < y_bound) {
        *arg1 = y_bound;
        result |= 0x1000;
    } else {
        y_bound = D_800FE508[3];
        if (y_bound < y) {
            *arg1 = y_bound;
            result |= 0x100;
        }
    }
    ASM_KEEP(y);
    ASM_KEEP(result);
    return result;
}
