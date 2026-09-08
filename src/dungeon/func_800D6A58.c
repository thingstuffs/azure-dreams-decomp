#include "common.h"
#include "m2c_compat.h"

extern s32 D_800E5910;

typedef struct S_800DC1B8_0 {
    u8 pad_00[0x18];
    s32 unk_18;
    u8 pad_1C[0x10];
    s32 unk_2C;
} S_800DC1B8_0;   /* temp_a1 in func_800DC1B8 */

/* Wraps the position by signed remainder modulo 32 plus 32 and stores the supplied value. */
void func_800DC1B8(s32 state_value) {
    s32 position;
    s32 adjusted_position;
    S_800DC1B8_0 *state;

    state = D_800E5910 + 0x20;
    position = state->unk_18;
    adjusted_position = position;
    if (position < 0) {
        adjusted_position = position + 0x1F;
    }
    state->unk_18 = (s32) ((position - ((adjusted_position >> 5) << 5)) + 0x20);
    state->unk_2C = state_value;
}
