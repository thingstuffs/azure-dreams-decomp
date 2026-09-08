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

/* Return whether two positions share a row, column, or diagonal. */
s32 func_800A365C(S_800A365C_0 *source, S_800A365C_1 *target, s32 aligned) {
    s32 target_y;
    s32 y_delta;
    s32 x_delta;

    x_delta = source->unk_24 - target->unk_24;
    ASM_USE(source);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    y_delta = source->unk_25;
    ASM_USE2(source, aligned);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    target_y = target->unk_25;
    if (x_delta < 0) {
        x_delta = 0 - x_delta;
    }
    y_delta = y_delta - target_y;
    if (y_delta < 0) {
        y_delta = 0 - y_delta;
    }
    aligned = 0;
    if ((x_delta == y_delta) || (x_delta == 0) || (y_delta == 0)) {
        aligned = 1;
    }
    return aligned;
}

/* MECHANISM: The frameless leaf keeps a dead third ABI argument as the a2 result home.
   ASM_USE(arg0) preserves the first load-delay nop; ASM_USE2(arg0, arg2) keeps
   a0/a2 occupied so the absolute deltas color v1/v0 and the second byte uses a0. */
