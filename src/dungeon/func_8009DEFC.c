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

static __inline__ s32 position_delta_abs(u8 a, u8 b) {
    return __builtin_abs(a - b);
}

/* Return whether two positions share a row, column, or diagonal. */
s32 func_800A365C(S_800A365C_0 *source, S_800A365C_1 *target, s32 aligned) {
    s32 y_delta;
    s32 x_delta;

    x_delta = position_delta_abs(source->unk_24, target->unk_24);
    y_delta = position_delta_abs(source->unk_25, target->unk_25);

    aligned = 0;
    if ((x_delta == y_delta) || (x_delta == 0) || (y_delta == 0)) {
        aligned = 1;
    }
    return aligned;
}

