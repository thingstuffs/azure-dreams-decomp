/* Midpoint tracking (G00574).
 * Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800A75EC, CL:town/func_800A76BC.
 */
#include "town/map/midpoint_tracking_g00574.h"
#include "town/map.h"

/* Restart tracking when the current point changes; otherwise update the midpoint. */
void restart_or_update_midpoint_tracking(TownCameraState *state) {
    IntVector3 *current;

    current = state->target;
    if (current != state->previous_target) {
        state->steps = 9;
        state->track_target = reset_or_advance_target_midpoint;
        state->unk14 = 0;
        state->unk18 = 0;
        state->unk1C = 0;
        state->previous_target = state->target;
        reset_or_advance_target_midpoint(state);
        return;
    }
    state->x = (current->x + state->other->x) / 2;
    state->y = (state->target->y + state->other->y) / 2;
    state->z = (state->target->z + state->other->z) / 2;
}

/* Reset on target changes or move toward the midpoint of the two targets. */
void reset_or_advance_target_midpoint(TownCameraState *state) {
    IntVector3 *target;

    target = state->target;
    if (target != state->previous_target) {
        state->steps = 9;
        state->unk14 = 0;
        state->unk18 = 0;
        state->unk1C = 0;
        state->previous_target = state->target;
        restart_or_update_midpoint_tracking(state);
        return;
    }
    state->x += (((target->x + state->other->x) / 2) - state->x) / state->steps;
    state->y += (((state->target->y + state->other->y) / 2) - state->y) / state->steps;
    state->z += (((state->target->z + state->other->z) / 2) - state->z) / state->steps;
    state->steps--;
    if (state->steps <= 0) {
        state->track_target = restart_or_update_midpoint_tracking;
    }
}
