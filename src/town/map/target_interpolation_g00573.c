/* Target interpolation (G00573).
 * Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800A7198, CL:town/func_800A7434, CL:town/func_800A74B0, CL:town/func_800A7588.
 */
#include "town/map/target_interpolation_g00573.h"

/* Reset state when the value source changes; otherwise copy its three values. */
void reset_or_copy_state_values(UnkStruct_800A7434 *state) {
    s32 *values;

    values = state->unk00;
    if (values != state->unk04) {
        state->unk20 = 9;
        state->unk28 = (void (*)(void))restart_or_advance_target_interpolation;
        state->unk14 = 0;
        state->unk18 = 0;
        state->unk1C = 0;
        state->unk04 = values;
        restart_or_advance_target_interpolation((S_800A4C10_0 *)state);
        return;
    }
    state->unk08 = values[0];
    state->unk0C = state->unk00[1];
    state->unk10 = state->unk00[2];
}

/* Restart interpolation when the target changes, otherwise advance toward its position. */
void restart_or_advance_target_interpolation(S_800A4C10_0 *state) {
    s32 steps_left;
    S_800A4C10_1 *target;

    target = state->unk_00;
    if (target != state->unk_04) {
        state->unk_20 = 9;
        state->unk_14 = 0;
        state->unk_18 = 0;
        state->unk_1C = 0;
        state->unk_04 = target;
        reset_or_copy_state_values((UnkStruct_800A7434 *)state);
        return;
    }
    state->unk_08 +=
        (target->unk_00 - state->unk_08) /
        state->unk_20;
    state->unk_0C +=
        (((S_800A4C10_2 *)(state->unk_00))->unk_04 - state->unk_0C) /
        state->unk_20;
    state->unk_10 +=
        (((S_800A4C10_2 *)(state->unk_00))->unk_08 - state->unk_10) /
        state->unk_20;
    steps_left = state->unk_20 - 1;
    state->unk_20 = steps_left;
    if (steps_left <= 0) {
        state->unk_28 = (s32 *)&reset_or_copy_state_values;
    }
}
