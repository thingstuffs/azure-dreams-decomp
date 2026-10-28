#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

extern void update_actor_behavior_facing_and_animation(ActorRecord *actor_arg, ObjectPosition *context_arg, SpriteFrameState *map_object_arg, ActorRecord *actor_state_arg);

/* jump_table; owner: dungeon/func_8107D768. */
const void *const tyrant_slot_a_behavior_targets[12] __attribute__((aligned(4))) = {
    ((u8 *)update_actor_behavior_facing_and_animation + 0x42C),
    ((u8 *)update_actor_behavior_facing_and_animation + 0x42C),
    ((u8 *)update_actor_behavior_facing_and_animation + 0x42C),
    ((u8 *)update_actor_behavior_facing_and_animation + 0x458),
    ((u8 *)update_actor_behavior_facing_and_animation + 0x3D8),
    ((u8 *)update_actor_behavior_facing_and_animation + 0x3D8),
    ((u8 *)update_actor_behavior_facing_and_animation + 0x3D8),
    ((u8 *)update_actor_behavior_facing_and_animation + 0x384),
    ((u8 *)update_actor_behavior_facing_and_animation + 0x3BC),
    ((u8 *)update_actor_behavior_facing_and_animation + 0x458),
    ((u8 *)update_actor_behavior_facing_and_animation + 0x458),
    ((u8 *)update_actor_behavior_facing_and_animation + 0x41C)
};
