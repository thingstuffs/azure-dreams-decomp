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

/* Stores the position the playback advances to after one step. */
static inline void playback_set_next(PlaybackState *state, s32 position, s32 step)
{
    state->next_position = position + step;
}

/* Updates the playback position and next position, returning 1 if playback has ended. */
s32 func_800597A8(PlaybackState *state)
{
    s32 updated_position;

    updated_position = func_800588C8(state->position);
    state->position = updated_position;
    if (updated_position == -1) {
        return 1;
    }
    state->step = func_80058ABC(state);
    state->previous_position = state->position;
    playback_set_next(state, state->position, state->step);
    return 0;
}
