#include "common.h"

typedef struct {
    u16 unk0;
    s16 limit;
    s16 current;
    u8 pad6[4];
    s16 target;
} Func818F9D8CState;

extern s16 D_800266BC[5];
extern s32 D_800814A0[3];

/* Updates a grayscale fade, advances its progress, and flags completion. */
void func_8002558C(Func818F9D8CState *state, s32 unused, u8 *out)
{
    s32 current;
    s32 target;
    s32 limit;
    s16 intensity;
    s16 next_step;

    current = state->current;
    target = state->target;
    D_800266BC[0] = 1;

    if (current < target) {
        intensity = (current * 0x60) / target;
        out[0xE] = intensity;
    } else {
        limit = state->limit;
        intensity = ((limit - current) * 0x60) / (limit - target);
        out[0xE] = intensity;
    }
    out[0xD] = intensity;
    out[0xC] = intensity;

    next_step = (u16)state->current + 1;
    state->current = next_step;
    if (next_step >= state->limit) {
        ((u16 *)state)[-1] |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }
}
