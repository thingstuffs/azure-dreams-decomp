#include "modules/town_door.h"

/* Advance the state counter and apply the next state when the check succeeds. */
void func_800A0DAC(S_800A0DAC_0 *state, s32 unused, s32 context_a, s32 context_b) {
    func_800A12B4(&D_80100B70, context_a, context_b);
    state->unk_6E = (u16)(state->unk_6E + 0x10);
    if (func_800A1080(&D_80100B70, context_a, context_b) != 0) {
        state->unk_6C = 0x20;
        state->unk_50 = &func_800A0E3C;
    }
}
