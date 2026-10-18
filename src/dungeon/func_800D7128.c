#include "common.h"


void update_state_activity_flags();
extern s32 D_800E5910;

typedef struct S_800DC888_0 {
    u8 pad_00[0x38];
    s32 * unk_38;
} S_800DC888_0;

// Advances the stored cycle index modulo three and applies the new index.
void advance_wrapped_cycle_index(void) {
    s32 *cycleIndexToWrap;
    s32 *cycleIndexToIncrement;
    s32 incrementedIndex;
    S_800DC888_0 *cycleState;

    cycleState = D_800E5910 + 0x20;
    cycleIndexToIncrement = cycleState->unk_38;
    *cycleIndexToIncrement += 1;
    cycleIndexToWrap = cycleState->unk_38;
    incrementedIndex = *cycleIndexToWrap;
    *cycleIndexToWrap = incrementedIndex % 3;
    update_state_activity_flags(cycleState);
}
