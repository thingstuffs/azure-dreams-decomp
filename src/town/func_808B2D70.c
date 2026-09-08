#include "common.h"
#include "m2c_compat.h"

typedef struct S_808B2D70_0 {
    u8 pad_00[0xE];
    u8 unk_0E;
} S_808B2D70_0;   /* temp_v1 in func_808B2D70 */

/* Writes back the state byte at offset 0x0E and returns the input value. */
s32 func_808B2D70(s32 value) {
    S_808B2D70_0 *state;

    state = *(void **)0xA0700F40;
    state->unk_0E = (u8) state->unk_0E;
    return value;
}
