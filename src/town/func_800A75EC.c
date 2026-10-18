#include "common.h"

typedef struct Func800A75ECState {
    s32 *current;
    s32 *previous;
    s32 center_x;
    s32 center_y;
    s32 center_z;
    s32 unk14;
    s32 unk18;
    s32 unk1c;
    s32 unk20;
    s32 unk24;
    void (*callback)(void *);
    s32 *other;
} Func800A75ECState;

extern void reset_or_advance_target_midpoint(void *state);

/* Restart tracking when the current point changes; otherwise update the midpoint. */
void restart_or_update_midpoint_tracking(Func800A75ECState *state) {
    s32 *current;

    current = state->current;
    if (current != state->previous) {
        state->unk20 = 9;
        state->callback = reset_or_advance_target_midpoint;
        state->unk14 = 0;
        state->unk18 = 0;
        state->unk1c = 0;
        state->previous = state->current;
        reset_or_advance_target_midpoint(state);
        return;
    }
    state->center_x = (current[0] + state->other[0]) / 2;
    state->center_y = (state->current[1] + state->other[1]) / 2;
    state->center_z = (state->current[2] + state->other[2]) / 2;
}
