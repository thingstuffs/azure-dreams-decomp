#include "common.h"

extern s32 D_800FE508[4];

s32 func_80096E08(s32 *arg0, s32 *arg1)
{
    s32 x;
    s32 y;
    s32 x_bound;
    s32 y_bound;
    register s32 result ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

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
            ASM_KEEP(x);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
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
    ASM_KEEP(y);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    return result;
}
