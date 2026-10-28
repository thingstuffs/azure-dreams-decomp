#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

extern void update_actor_behavior_variant_g(ActorRecord *controller, ObjectPosition *context, SpriteFrameState *entity, ActorRecord *actor_state);

/* jump_table; owner: dungeon/func_80A1D684. */
const void *const ifrit_slot_g_behavior_targets[12] __attribute__((aligned(4))) = {
    ((u8 *)update_actor_behavior_variant_g + 0x3C8),
    ((u8 *)update_actor_behavior_variant_g + 0x3C8),
    ((u8 *)update_actor_behavior_variant_g + 0x3C8),
    ((u8 *)update_actor_behavior_variant_g + 0x3F4),
    ((u8 *)update_actor_behavior_variant_g + 0x374),
    ((u8 *)update_actor_behavior_variant_g + 0x374),
    ((u8 *)update_actor_behavior_variant_g + 0x374),
    ((u8 *)update_actor_behavior_variant_g + 0x33C),
    ((u8 *)update_actor_behavior_variant_g + 0x33C),
    ((u8 *)update_actor_behavior_variant_g + 0x3F4),
    ((u8 *)update_actor_behavior_variant_g + 0x3F4),
    ((u8 *)update_actor_behavior_variant_g + 0x3B8)
};
