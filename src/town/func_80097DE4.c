#include "common.h"

typedef struct TownMotionState {
    u8 pad_00[0xC];
    s32 x;
    s32 y;
    s32 z;
} TownMotionState;

extern u8 D_800CFCEE[9];
extern void townClearSlotN3CopiesSlotN0(TownMotionState *state);
extern void townClearTheGlobalStateSFifthWordCopySourceSSecond(TownMotionState *state);
extern void townClearGlobalSlotN5CopySourceSlotN2GlobalSlotN2(TownMotionState *state);

/* Clear motion along blocked directions and update the affected axes. */
void townClearMotionAlongBlockedDirectionsUpdateAffectedAxes(TownMotionState *state)
{
    if (D_800CFCEE[2] != 0 && state->x < 0) {
        state->x = 0;
        townClearSlotN3CopiesSlotN0(state);
    }

    if (D_800CFCEE[3] != 0 && state->x > 0) {
        state->x = 0;
        townClearSlotN3CopiesSlotN0(state);
    }

    if (D_800CFCEE[4] != 0 && state->y < 0) {
        state->y = 0;
        townClearTheGlobalStateSFifthWordCopySourceSSecond(state);
    }

    if (D_800CFCEE[5] != 0 && state->y > 0) {
        state->y = 0;
        townClearTheGlobalStateSFifthWordCopySourceSSecond(state);
    }

    if (D_800CFCEE[1] != 0 && state->z > 0) {
        state->z = 0;
        townClearGlobalSlotN5CopySourceSlotN2GlobalSlotN2(state);
    }

    if (D_800CFCEE[0] != 0 && state->z < 0) {
        state->z = 0;
        townClearGlobalSlotN5CopySourceSlotN2GlobalSlotN2(state);
    }
}
