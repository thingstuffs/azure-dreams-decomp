#include "common.h"
#include "shared/sprite_frame_state.h"
#include "records/Rec_func_80094268_arg0.h"

/* Pointer arguments follow the matched initialize_object_entries body. */
extern void initialize_object_entries(void *state, SpriteFrameState *output, s32 *entries);

extern s32 person_reaction_object_entries[];
extern u8 D_800CDA6C[];

typedef struct ReactionState {
    u8 pad_00[0x14];
    s32 fixed_state;
} ReactionState;

void initialize_actor_reaction_and_fixed_state(Rec_func_80094268_arg0 *actor, ReactionState *state, SpriteFrameState *output) {
    initialize_object_entries(actor, output, person_reaction_object_entries);
    actor->unk_50.as_pv = D_800CDA6C;
    state->fixed_state = -10 * 0x10000;
}
