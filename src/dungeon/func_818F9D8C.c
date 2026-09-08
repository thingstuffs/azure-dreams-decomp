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

void func_8002558C(Func818F9D8CState *state, s32 unused, u8 *out)
{
    s32 current;
    s32 target;
    s32 limit;
    register s32 value ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    s16 next;

    current = state->current;
    target = state->target;
    D_800266BC[0] = 1;

    if (current < target) {
        value = (current * 0x60) / target;
        out[0xE] = value;
    } else {
        limit = state->limit;
        value = ((limit - current) * 0x60) / (limit - target);
        out[0xE] = value;
    }
    out[0xD] = value;
    out[0xC] = value;

    next = (u16)state->current + 1;
    state->current = next;
    if (next >= state->limit) {
        ((u16 *)state)[-1] |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }
}
