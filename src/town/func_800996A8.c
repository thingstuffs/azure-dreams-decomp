#include "common.h"

extern s32 D_800FE508[4];

s32 func_80096E08(s32 *arg0, s32 *arg1)
{
    s32 x;
    s32 y;
    s32 x_bound;
    s32 y_bound;
    register s32 result ASM_REG("$3");   /* MATCH pin: load-bearing for the whole function shape */

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
            ASM_KEEP(x);   /* MATCH pin: retail schedule: same instructions, different order without it */
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
    ASM_KEEP(y);   /* MATCH pin: retail schedule: same instructions, different order without it */
    return result;
}
