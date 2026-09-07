#include "common.h"

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

s32 func_800A365C(void *arg0, void *arg1, s32 arg2) {
    s32 var_a0;
    s32 var_v0;
    s32 var_v1;

    var_v1 = M2C_FIELD(arg0, u8 *, 0x24) - M2C_FIELD(arg1, u8 *, 0x24);
    ASM_USE(arg0);
    var_v0 = M2C_FIELD(arg0, u8 *, 0x25);
    ASM_USE2(arg0, arg2);
    var_a0 = M2C_FIELD(arg1, u8 *, 0x25);
    if (var_v1 < 0) {
        var_v1 = 0 - var_v1;
    }
    var_v0 = var_v0 - var_a0;
    if (var_v0 < 0) {
        var_v0 = 0 - var_v0;
    }
    arg2 = 0;
    if ((var_v1 == var_v0) || (var_v1 == 0) || (var_v0 == 0)) {
        arg2 = 1;
    }
    return arg2;
}

/* MECHANISM: The frameless leaf keeps a dead third ABI argument as the a2 result home.
   ASM_USE(arg0) preserves the first load-delay nop; ASM_USE2(arg0, arg2) keeps
   a0/a2 occupied so the absolute deltas color v1/v0 and the second byte uses a0. */
