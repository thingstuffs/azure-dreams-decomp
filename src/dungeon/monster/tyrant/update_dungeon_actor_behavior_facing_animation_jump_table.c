#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

extern void update_a_dungeon_actor_s_behavior_facing_animation_state(ActorRecord *actor_arg, ObjectPosition *context_arg, SpriteFrameState *map_object_arg, ActorRecord *actor_state_arg);

/* jump_table; owner: dungeon/func_81071768. */
const void *const tyrant_slot_c_behavior_targets[12] __attribute__((aligned(4))) = {
    ((u8 *)update_a_dungeon_actor_s_behavior_facing_animation_state + 0x42C),
    ((u8 *)update_a_dungeon_actor_s_behavior_facing_animation_state + 0x42C),
    ((u8 *)update_a_dungeon_actor_s_behavior_facing_animation_state + 0x42C),
    ((u8 *)update_a_dungeon_actor_s_behavior_facing_animation_state + 0x458),
    ((u8 *)update_a_dungeon_actor_s_behavior_facing_animation_state + 0x3D8),
    ((u8 *)update_a_dungeon_actor_s_behavior_facing_animation_state + 0x3D8),
    ((u8 *)update_a_dungeon_actor_s_behavior_facing_animation_state + 0x3D8),
    ((u8 *)update_a_dungeon_actor_s_behavior_facing_animation_state + 0x384),
    ((u8 *)update_a_dungeon_actor_s_behavior_facing_animation_state + 0x3BC),
    ((u8 *)update_a_dungeon_actor_s_behavior_facing_animation_state + 0x458),
    ((u8 *)update_a_dungeon_actor_s_behavior_facing_animation_state + 0x458),
    ((u8 *)update_a_dungeon_actor_s_behavior_facing_animation_state + 0x41C)
};
