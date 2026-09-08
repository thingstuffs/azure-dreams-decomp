#include "common.h"
#include "m2c_compat.h"

extern s32 D_80175D50;

typedef struct S_8016F304_0 {
    u8 pad_00[0x96];
    s16 unk_96;
    u8 pad_98[0x2];
    s8 unk_9A;
    s8 unk_9B;
} S_8016F304_0;   /* temp_v0 in func_8016F304 */

/* Sets the state ID and clears the associated byte and halfword. */
void func_8016F304(s8 state_id) {
    S_8016F304_0 *state;

    state = D_80175D50 + 0x20;
    state->unk_9A = state_id;
    state->unk_9B = 0;
    state->unk_96 = 0;
}
