#include "common.h"
#include "shared/object_node.h"


typedef void (*Callback)(void *, s32);

extern void townRefreshFormattedGlobalDisplay(void *);


typedef struct S_800B1890_0 {
    u8 pad_00[0x8];
    union { s16 s; u16 u; } unk_08;   /* accessed as both */
} S_800B1890_0;

typedef struct ValueTransition {
    s32 unused;
    union { s32 word; u16 low_half; } target;
    u8 pad_08[0x34];
    void *state;
} ValueTransition;

/* Lowers the state's value toward the target, or snaps to it and switches callbacks. */
void townLowerValueTowardTarget(void *object) {
    S_800B1890_0 *state;
    s32 target_value;
    s32 current_value;
    u16 current_bits;
    s32 adjustment;

    state = ((ValueTransition *)object)->state;
    target_value = ((ValueTransition *)object)->target.word;
    current_value = state->unk_08.s;
    current_bits = state->unk_08.u;
    if (target_value < current_value) {
        adjustment = current_value + 4;
        adjustment = target_value - adjustment;
        adjustment >>= 2;
        state->unk_08.s = current_bits + adjustment;
    } else {
        state->unk_08.u = ((ValueTransition *)object)->target.low_half;
        ((ObjectNodeHeader *)object)[-1].unk_10 = townRefreshFormattedGlobalDisplay;
    }

    townRefreshFormattedGlobalDisplay(object);
}
