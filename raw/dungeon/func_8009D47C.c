#include "common.h"

extern s32 D_80083460[3];

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

s32 func_800A2BDC(void) {
    s32 *p = D_80083460;

    if (M2C_FIELD(p, s32 *, 0xC) != 0) {
        goto ret_one;
    }
    if (M2C_FIELD(p, s32 *, 0x10) != 0) {
        goto ret_one;
    }
    if (M2C_FIELD(p, s32 *, 0x8) != 0) {
        goto ret_one;
    }
    if ((M2C_FIELD(p, u16 *, 2) & 0x2008) != 0) {
        goto ret_one;
    }
    goto ret_zero;

ret_one:
    return 1;

ret_zero:
    return 0;
}
