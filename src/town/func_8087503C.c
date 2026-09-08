#include "common.h"
#include "m2c_compat.h"

typedef struct S_8087503C_0 {
    u8 pad_00[0x30];
    s32 unk_30;
} S_8087503C_0;   /* temp_a1 in func_8087503C */

/* Clears bit 30 in the global state's flags and returns the supplied value. */
s32 func_8087503C(s32 result) {
    S_8087503C_0 *state;

    state = *(void **)0x80701968;
    state->unk_30 = (s32) (state->unk_30 & 0xBFFFFFFF);
    return result;
}
