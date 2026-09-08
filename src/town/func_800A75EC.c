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

extern void func_800A4E1C(void *arg0);

/* Restart tracking when the current point changes; otherwise update the midpoint. */
void func_800A4D4C(Func800A75ECState *state) {
    s32 *current;

    current = state->current;
    if (current != state->previous) {
        state->unk20 = 9;
        state->callback = func_800A4E1C;
        state->unk14 = 0;
        state->unk18 = 0;
        state->unk1c = 0;
        state->previous = state->current;
        func_800A4E1C(state);
        return;
    }
    state->center_x = (current[0] + state->other[0]) / 2;
    state->center_y = (state->current[1] + state->other[1]) / 2;
    state->center_z = (state->current[2] + state->other[2]) / 2;
}
