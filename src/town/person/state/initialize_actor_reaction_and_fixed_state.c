#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/town_object.h"
#include "town/person/state.h"
#include "town/person/object.h"
#include "town/data.h"

/* Pointer arguments follow the matched initialize_object_entries body. */

extern u8 D_800CDA6C[];

typedef struct ReactionState {
    u8 pad_00[0x14];
    s32 fixed_state;
} ReactionState;

void initialize_actor_reaction_and_fixed_state(TownObjectRecord *actor, ReactionState *state, SpriteFrameState *output) {
    initialize_object_entries(actor, output, person_reaction_object_entries);
    actor->unk_50.as_pv = D_800CDA6C;
    state->fixed_state = -10 * 0x10000;
}
