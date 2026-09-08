#include "common.h"

typedef struct {
    u8 target0[3];
    u8 pad03;
    u16 value4;
    u16 value6;
    u8 pad08[0x40];
    s16 shift;
    s16 mode;
    s16 count;
    s16 angle;
    u8 pad50[8];
    u16 delta;
} State;

typedef struct {
    u8 pad00[2];
    s16 value2;
    u8 pad06[2];
    s16 value6;
} Output;

typedef struct {
    u8 pad00[0x0c];
    u8 value0c;
    u8 value0d;
    u8 value0e;
    u8 pad0f[0x0b];
    s16 value1a;
} Interp;

extern s32 D_800814A0[3];
extern s32 func_800644B8(s16);
extern s32 func_80064584(s16);

/* Updates angular motion and fades three channels in, holds them, then fades them out. */
void func_800BBBE0(State *state, Output *output, Interp *interp) {
    output->value2 = state->value4 + (func_80064584(state->angle) >> state->shift);
    output->value6 = state->value6 + (func_800644B8(state->angle) >> state->shift);
    state->angle = state->angle + state->delta;
    interp->value1a = state->angle + 0x400;

    if (state->mode == 0) {
        interp->value0c = interp->value0c + (state->target0[0] - interp->value0c) / state->count;
        interp->value0d = interp->value0d + (state->target0[1] - interp->value0d) / state->count;
        interp->value0e = interp->value0e + (state->target0[2] - interp->value0e) / state->count;
        state->count = state->count - 1;
        if (state->count <= 0) {
            state->count = 8;
            state->mode = state->mode + 1;
        }
    } else if (state->mode == 1) {
        state->count = state->count - 1;
        if (state->count <= 0) {
            state->count = 4;
            state->mode = state->mode + 1;
        }
    } else {
        interp->value0c = interp->value0c - interp->value0c / state->count;
        interp->value0d = interp->value0d - interp->value0d / state->count;
        interp->value0e = interp->value0e - interp->value0e / state->count;
        state->count = state->count - 1;
        if (state->count <= 0) {
            *((u16 *)state - 1) |= 0x8000;
            D_800814A0[0] |= 0x8000;
        }
    }
}
