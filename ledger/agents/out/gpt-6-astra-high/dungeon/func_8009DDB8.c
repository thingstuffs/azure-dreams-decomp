#include "common.h"
#include "m2c_compat.h"

typedef struct S_800A3518_0 {
    u8 pad_00[0x11];
    u8 unk_11;
    u8 pad_12[0x16];
    u8 unk_28;
    u8 unk_29;
} S_800A3518_0;   /* arg0 in func_800A3518 */

/* Checks whether the scaled value reaches the stored threshold. */
s32 func_800A3518(S_800A3518_0 *state) {
    return ((s32) state->unk_29 / (s32) (((u8) state->unk_11 >> 1) + 2)) >= (s32) state->unk_28;
}
