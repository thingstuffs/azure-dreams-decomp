#include "common.h"

/* manual g1 strike 2: order the negative-direction compare like retail */
#include "common.h"

typedef struct S_80056800_0 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x28];
    s32 unk_34;
    s16 unk_38;
    s16 unk_3A;
    u8 pad_3C[0x4];
    s16 unk_40;
} S_80056800_0;   /* arg0 in func_80056800 */

/* Step the enabled oscillation between its limits, or reset its value to zero. */
void func_80056800(S_80056800_0 *state) {
    s32 next_value;
    s32 lower_limit;

    if (state->unk_08 != 0) {
        if (state->unk_34 != 0) {
            if ((state->unk_3A + state->unk_38) < state->unk_40) {
                state->unk_3A = (u16)state->unk_3A + (u16)state->unk_38;
                return;
            }
            state->unk_34 = 0;
            state->unk_3A = (u16)state->unk_40;
            return;
        }

        next_value = state->unk_3A - state->unk_38;
        lower_limit = -state->unk_40;
        if (lower_limit < next_value) {
            state->unk_3A = (u16)state->unk_3A - (u16)state->unk_38;
            return;
        }
        state->unk_34 = 1;
        state->unk_3A = -((s16)(u16)state->unk_40);
        return;
    }
    state->unk_3A = 0;
}
