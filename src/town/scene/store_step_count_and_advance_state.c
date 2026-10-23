#include "common.h"
#include "shared/record_ptrs.h"

extern s32 scene_progress_step;
typedef struct { u8 pad[0x110]; s32 counter; } StepState;

/* Store the step count and advance the state counter by twice that count plus one. */
void store_step_count_and_advance_state(s32 step_count) {
    void *root;
    StepState *state;
    s32 counter;

    root = town_scene_root;
    state = *(void **)((s8 *)root + 0x40);
    counter = state->counter;
    scene_progress_step = step_count;
    counter = counter + 1;
    counter = counter + (step_count * 2);
    state->counter = counter;
}
