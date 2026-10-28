#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

extern void update_dungeon_actor_behavior_and_targets(ActorRecord *controller, ObjectPosition *context, SpriteFrameState *entity, ActorRecord *actor_state);

/* jump_table; owner: dungeon/func_80A41684. */
const void *const ifrit_slot_a_behavior_targets[12] __attribute__((aligned(4))) = {
    ((u8 *)update_dungeon_actor_behavior_and_targets + 0x3C8),
    ((u8 *)update_dungeon_actor_behavior_and_targets + 0x3C8),
    ((u8 *)update_dungeon_actor_behavior_and_targets + 0x3C8),
    ((u8 *)update_dungeon_actor_behavior_and_targets + 0x3F4),
    ((u8 *)update_dungeon_actor_behavior_and_targets + 0x374),
    ((u8 *)update_dungeon_actor_behavior_and_targets + 0x374),
    ((u8 *)update_dungeon_actor_behavior_and_targets + 0x374),
    ((u8 *)update_dungeon_actor_behavior_and_targets + 0x33C),
    ((u8 *)update_dungeon_actor_behavior_and_targets + 0x33C),
    ((u8 *)update_dungeon_actor_behavior_and_targets + 0x3F4),
    ((u8 *)update_dungeon_actor_behavior_and_targets + 0x3F4),
    ((u8 *)update_dungeon_actor_behavior_and_targets + 0x3B8)
};
