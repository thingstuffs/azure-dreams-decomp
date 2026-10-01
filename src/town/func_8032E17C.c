#include "common.h"
#include "shared/record_ptrs.h"

extern s32 D_8001C368;
typedef struct { u8 pad[0x110]; s32 counter; } StepState;

/* Store the step count and advance the state counter by twice that count plus one. */
void func_8001897C(s32 step_count) {
    void *root;
    StepState *state;
    s32 counter;

    root = D_80016000;
    state = *(void **)((s8 *)root + 0x40);
    counter = state->counter;
    D_8001C368 = step_count;
    counter = counter + 1;
    counter = counter + (step_count * 2);
    state->counter = counter;
}
