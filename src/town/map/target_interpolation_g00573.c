/* Target interpolation (G00573).
 * Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800A7198, CL:town/func_800A7434, CL:town/func_800A74B0, CL:town/func_800A7588.
 */
#include "town/map/target_interpolation_g00573.h"
#include "town/map.h"

/* Reset state when the value source changes; otherwise copy its three values. */
void reset_or_copy_state_values(TownCameraState *state) {
    IntVector3 *values;

    values = state->target;
    if (values != state->previous_target) {
        state->steps = 9;
        state->track_target = restart_or_advance_target_interpolation;
        state->unk14 = 0;
        state->unk18 = 0;
        state->unk1C = 0;
        state->previous_target = values;
        restart_or_advance_target_interpolation(state);
        return;
    }
    state->x = values->x;
    state->y = state->target->y;
    state->z = state->target->z;
}

/* Restart interpolation when the target changes, otherwise advance toward its position. */
void restart_or_advance_target_interpolation(TownCameraState *state) {
    s32 steps_left;
    IntVector3 *target;

    target = state->target;
    if (target != state->previous_target) {
        state->steps = 9;
        state->unk14 = 0;
        state->unk18 = 0;
        state->unk1C = 0;
        state->previous_target = target;
        reset_or_copy_state_values(state);
        return;
    }
    state->x += (target->x - state->x) / state->steps;
    state->y += (state->target->y - state->y) / state->steps;
    state->z += (state->target->z - state->z) / state->steps;
    steps_left = state->steps - 1;
    state->steps = steps_left;
    if (steps_left <= 0) {
        state->track_target = reset_or_copy_state_values;
    }
}
