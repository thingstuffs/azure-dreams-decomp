#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

extern void advance_actor_action_variant_b(ActorRecord *actor_in, ObjectPosition *actor_data_in, SpriteFrameState *sprite_in, ActorRecord *status_in);

/* jump_table; owner: dungeon/func_80EF24E8. */
const void *const D_8015E840[12] __attribute__((aligned(4))) = {
    ((u8 *)advance_actor_action_variant_b + 0x3E4),
    ((u8 *)advance_actor_action_variant_b + 0x3E4),
    ((u8 *)advance_actor_action_variant_b + 0x3E4),
    ((u8 *)advance_actor_action_variant_b + 0x410),
    ((u8 *)advance_actor_action_variant_b + 0x390),
    ((u8 *)advance_actor_action_variant_b + 0x390),
    ((u8 *)advance_actor_action_variant_b + 0x390),
    ((u8 *)advance_actor_action_variant_b + 0x33C),
    ((u8 *)advance_actor_action_variant_b + 0x374),
    ((u8 *)advance_actor_action_variant_b + 0x410),
    ((u8 *)advance_actor_action_variant_b + 0x410),
    ((u8 *)advance_actor_action_variant_b + 0x3D4)
};
