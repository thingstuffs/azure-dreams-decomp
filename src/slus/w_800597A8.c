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
    register s32 position ASM_REG("$3");   /* MATCH pin: slus-diff */
    s32 next;
    register u32 raw ASM_REG("$2");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */

    result = func_800588C8(state->position);
    state->position = result;
    if (result == -1) {
        return 1;
    }

    raw = func_80058ABC(state);
    state->step = raw;
    ASM_KEEP(raw);   /* MATCH pin: slus-diff */
    step = raw;
    ASM_KEEP_NV(step);   /* MATCH pin: slus-diff */
    position = state->position;
    next = position;
    ASM_KEEP_NV(next);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    next += step;
    state->previous_position = position;
    state->next_position = next;
    return 0;
}
