#include "common.h"
#include "records/Rec_func_80094268_arg0.h"

/* Pointer arguments follow the matched townInitializeObjectEntries body. */
extern void townInitializeObjectEntries(void *state, s8 *output, s32 *entries);

extern s32 D_800D72D4[];
extern u8 D_800CDA6C[];

typedef struct ReactionState {
    u8 pad_00[0x14];
    s32 fixed_state;
} ReactionState;

void initialize_actor_reaction_and_fixed_state(Rec_func_80094268_arg0 *actor, ReactionState *state, s8 *output) {
    townInitializeObjectEntries(actor, output, D_800D72D4);
    actor->unk_50.as_pv = D_800CDA6C;
    state->fixed_state = -10 * 0x10000;
}
