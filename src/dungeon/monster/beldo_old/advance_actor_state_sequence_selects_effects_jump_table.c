#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

extern void advance_the_actor_state_sequence_selects_effects_facing_direction(ActorRecord *action, ObjectPosition *context, SpriteFrameState *entity, ActorRecord *actor);

/* jump_table; owner: dungeon/func_8127D6C4. */
const void *const D_8016F880[6] __attribute__((aligned(4))) = {
    ((u8 *)advance_the_actor_state_sequence_selects_effects_facing_direction + 0x5C),
    ((u8 *)advance_the_actor_state_sequence_selects_effects_facing_direction + 0xCC),
    ((u8 *)advance_the_actor_state_sequence_selects_effects_facing_direction + 0xE4),
    ((u8 *)advance_the_actor_state_sequence_selects_effects_facing_direction + 0x110),
    ((u8 *)advance_the_actor_state_sequence_selects_effects_facing_direction + 0x38C),
    ((u8 *)advance_the_actor_state_sequence_selects_effects_facing_direction + 0x3FC)
};
