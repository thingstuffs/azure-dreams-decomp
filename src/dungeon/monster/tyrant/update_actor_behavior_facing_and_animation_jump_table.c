#include "common.h"

extern void update_actor_behavior_facing_and_animation(void);

/* jump_table; owner: dungeon/func_8107D768. */
const u32 tyrant_slot_a_behavior_targets[12] __attribute__((aligned(4))) = {
    (u32)((u8 *)update_actor_behavior_facing_and_animation + 0x42C),
    (u32)((u8 *)update_actor_behavior_facing_and_animation + 0x42C),
    (u32)((u8 *)update_actor_behavior_facing_and_animation + 0x42C),
    (u32)((u8 *)update_actor_behavior_facing_and_animation + 0x458),
    (u32)((u8 *)update_actor_behavior_facing_and_animation + 0x3D8),
    (u32)((u8 *)update_actor_behavior_facing_and_animation + 0x3D8),
    (u32)((u8 *)update_actor_behavior_facing_and_animation + 0x3D8),
    (u32)((u8 *)update_actor_behavior_facing_and_animation + 0x384),
    (u32)((u8 *)update_actor_behavior_facing_and_animation + 0x3BC),
    (u32)((u8 *)update_actor_behavior_facing_and_animation + 0x458),
    (u32)((u8 *)update_actor_behavior_facing_and_animation + 0x458),
    (u32)((u8 *)update_actor_behavior_facing_and_animation + 0x41C)
};
