#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

extern void update_actor_behavior_variant_h(ActorRecord *motion, ObjectPosition *render_ctx, SpriteFrameState *map_entity, ActorRecord *actor);

/* jump_table; owner: dungeon/func_80D35F60. */
const void *const noise_slot_a_behavior_targets[12] __attribute__((aligned(4))) = {
    ((u8 *)update_actor_behavior_variant_h + 0x3F8),
    ((u8 *)update_actor_behavior_variant_h + 0x3F8),
    ((u8 *)update_actor_behavior_variant_h + 0x3F8),
    ((u8 *)update_actor_behavior_variant_h + 0x424),
    ((u8 *)update_actor_behavior_variant_h + 0x3A4),
    ((u8 *)update_actor_behavior_variant_h + 0x3A4),
    ((u8 *)update_actor_behavior_variant_h + 0x3A4),
    ((u8 *)update_actor_behavior_variant_h + 0x350),
    ((u8 *)update_actor_behavior_variant_h + 0x388),
    ((u8 *)update_actor_behavior_variant_h + 0x424),
    ((u8 *)update_actor_behavior_variant_h + 0x424),
    ((u8 *)update_actor_behavior_variant_h + 0x3E8)
};
