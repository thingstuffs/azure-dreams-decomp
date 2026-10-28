#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

extern void advance_actor_action_variant_c(ActorRecord *action, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor);

/* jump_table; owner: dungeon/func_80EF3FB0. */
const void *const D_8015E8A0[7] __attribute__((aligned(4))) = {
    ((u8 *)advance_actor_action_variant_c + 0x110),
    ((u8 *)advance_actor_action_variant_c + 0x108),
    ((u8 *)advance_actor_action_variant_c + 0x100),
    ((u8 *)advance_actor_action_variant_c + 0x118),
    ((u8 *)advance_actor_action_variant_c + 0xBC),
    ((u8 *)advance_actor_action_variant_c + 0xB4),
    ((u8 *)advance_actor_action_variant_c + 0xAC)
};
