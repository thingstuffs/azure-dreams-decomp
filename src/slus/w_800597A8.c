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

s32 func_800597A8(PlaybackState *state)
{
    s32 result;
    u32 step;
    register s32 position ASM_REG("$3");   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
    s32 next;
    register u32 raw ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */

    result = func_800588C8(state->position);
    state->position = result;
    if (result == -1) {
        return 1;
    }

    raw = func_80058ABC(state);
    state->step = raw;
    ASM_KEEP(raw);   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
    step = raw;
    ASM_KEEP_NV(step);   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
    position = state->position;
    next = position;
    ASM_KEEP_NV(next);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    next += step;
    state->previous_position = position;
    state->next_position = next;
    return 0;
}
