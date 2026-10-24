#include "common.h"

extern void update_dungeon_actor_behavior_and_animation(void);

/* jump_table; owner: dungeon/func_8106B768. */
const void *const tyrant_slot_d_behavior_targets[12] __attribute__((aligned(4))) = {
    ((u8 *)update_dungeon_actor_behavior_and_animation + 0x42C),
    ((u8 *)update_dungeon_actor_behavior_and_animation + 0x42C),
    ((u8 *)update_dungeon_actor_behavior_and_animation + 0x42C),
    ((u8 *)update_dungeon_actor_behavior_and_animation + 0x458),
    ((u8 *)update_dungeon_actor_behavior_and_animation + 0x3D8),
    ((u8 *)update_dungeon_actor_behavior_and_animation + 0x3D8),
    ((u8 *)update_dungeon_actor_behavior_and_animation + 0x3D8),
    ((u8 *)update_dungeon_actor_behavior_and_animation + 0x384),
    ((u8 *)update_dungeon_actor_behavior_and_animation + 0x3BC),
    ((u8 *)update_dungeon_actor_behavior_and_animation + 0x458),
    ((u8 *)update_dungeon_actor_behavior_and_animation + 0x458),
    ((u8 *)update_dungeon_actor_behavior_and_animation + 0x41C)
};
