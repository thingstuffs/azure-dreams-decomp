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
    register u32 step ASM_REG("$5");
    register s32 position ASM_REG("$3");
    register s32 next ASM_REG("$4");
    register u32 raw ASM_REG("$2");

    result = func_800588C8(state->position);
    state->position = result;
    if (result == -1) {
        return 1;
    }

    raw = func_80058ABC(state);
    state->step = raw;
    ASM_KEEP(raw);
    step = raw;
    ASM_KEEP_NV(step);
    position = state->position;
    next = position;
    ASM_KEEP_NV(next);
    next += step;
    state->previous_position = position;
    state->next_position = next;
    return 0;
}
