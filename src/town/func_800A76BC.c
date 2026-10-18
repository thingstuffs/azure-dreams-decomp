#include "common.h"
#include "shared/types3a_types.h"


typedef struct TownTransition {
    IntVector3 *target;
    IntVector3 *previous_target;
    s32 x;
    s32 y;
    s32 z;
    s32 unk14;
    s32 unk18;
    s32 unk1C;
    s32 steps;
    s32 unk24;
    void (*callback)(void *, void *);
    IntVector3 *other;
} TownTransition;

extern void restart_or_update_midpoint_tracking(void *state);

/* Reset on target changes or move toward the midpoint of the two targets. */
void reset_or_advance_target_midpoint(TownTransition *state) {
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

    state->x += (((target->x + state->other->x) / 2) - state->x) /
                state->steps;
    state->y +=
        (((state->target->y + state->other->y) / 2) - state->y) /
        state->steps;
    state->z +=
        (((state->target->z + state->other->z) / 2) - state->z) /
        state->steps;
    state->steps--;
    if (state->steps <= 0) {
        state->callback = restart_or_update_midpoint_tracking;
    }
}
