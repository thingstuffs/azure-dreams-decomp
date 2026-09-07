#include "common.h"

typedef struct TownMotionState {
    u8 pad_00[0xC];
    s32 x;
    s32 y;
    s32 z;
} TownMotionState;

extern u8 D_800CFCEE[9];
extern void func_800954C4(TownMotionState *state);
extern void func_800954DC(TownMotionState *state);
extern void func_800954F4(TownMotionState *state);

void func_80095544(TownMotionState *state)
{
    if (D_800CFCEE[2] != 0 && state->x < 0) {
        state->x = 0;
        func_800954C4(state);
    }

    if (D_800CFCEE[3] != 0 && state->x > 0) {
        state->x = 0;
        func_800954C4(state);
    }

    if (D_800CFCEE[4] != 0 && state->y < 0) {
        state->y = 0;
        func_800954DC(state);
    }

    if (D_800CFCEE[5] != 0 && state->y > 0) {
        state->y = 0;
        func_800954DC(state);
    }

    if (D_800CFCEE[1] != 0 && state->z > 0) {
        state->z = 0;
        func_800954F4(state);
    }

    if (D_800CFCEE[0] != 0 && state->z < 0) {
        state->z = 0;
        func_800954F4(state);
    }
}
