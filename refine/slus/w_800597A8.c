#include "common.h"

typedef struct PlaybackState {
    s32 position;
    s32 pad04[5];
    s32 step;
    s32 next_position;
    s32 pad20[6];
    s32 previous_position;
} PlaybackState;

extern s32 func_800588C8(s32);
extern u32 func_80058ABC(PlaybackState *);

/* Updates the playback position and next position, returning 1 if playback has ended. */
s32 func_800597A8(PlaybackState *state)
{
    s32 updated_position;
    u32 step;
    register s32 position ASM_REG("$3");   /* MATCH pin: slus-diff */
    s32 next_position;
    register u32 step_value ASM_REG("$2");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */

    updated_position = func_800588C8(state->position);
    state->position = updated_position;
    if (updated_position == -1) {
        return 1;
    }

    step_value = func_80058ABC(state);
    state->step = step_value;
    ASM_KEEP(step_value);   /* MATCH pin: slus-diff */
    step = step_value;
    ASM_KEEP_NV(step);   /* MATCH pin: slus-diff */
    position = state->position;
    next_position = position;
    ASM_KEEP_NV(next_position);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    next_position += step;
    state->previous_position = position;
    state->next_position = next_position;
    return 0;
}
