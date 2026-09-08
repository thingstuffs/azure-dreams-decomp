#include "common.h"



#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

typedef struct S_800A365C_0 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_800A365C_0;   /* arg0 in func_800A365C */

typedef struct S_800A365C_1 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_800A365C_1;   /* arg1 in func_800A365C */

s32 func_800A365C(S_800A365C_0 *arg0, S_800A365C_1 *arg1, s32 arg2) {
    s32 var_a0;
    s32 var_v0;
    s32 var_v1;

    var_v1 = arg0->unk_24 - arg1->unk_24;
    ASM_USE(arg0);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    var_v0 = arg0->unk_25;
    ASM_USE2(arg0, arg2);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    var_a0 = arg1->unk_25;
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
