#include "common.h"

extern void update_actor_dungeon_behavior_and_animation(void);

/* Exact jump_table span; dispatch consumer dungeon/func_80DBA620. */
const void *const blume_slot_g_behavior_targets[12] __attribute__((aligned(4))) = {
    ((u8 *)update_actor_dungeon_behavior_and_animation + 0x3E4),
    ((u8 *)update_actor_dungeon_behavior_and_animation + 0x3E4),
    ((u8 *)update_actor_dungeon_behavior_and_animation + 0x3E4),
    ((u8 *)update_actor_dungeon_behavior_and_animation + 0x410),
    ((u8 *)update_actor_dungeon_behavior_and_animation + 0x390),
    ((u8 *)update_actor_dungeon_behavior_and_animation + 0x390),
    ((u8 *)update_actor_dungeon_behavior_and_animation + 0x390),
    ((u8 *)update_actor_dungeon_behavior_and_animation + 0x33C),
    ((u8 *)update_actor_dungeon_behavior_and_animation + 0x374),
    ((u8 *)update_actor_dungeon_behavior_and_animation + 0x410),
    ((u8 *)update_actor_dungeon_behavior_and_animation + 0x410),
    ((u8 *)update_actor_dungeon_behavior_and_animation + 0x3D4)
};
