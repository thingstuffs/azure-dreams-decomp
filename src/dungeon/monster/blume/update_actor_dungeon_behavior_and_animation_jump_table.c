#include "common.h"

extern void update_actor_dungeon_behavior_and_animation(void);

/* Exact jump_table span; dispatch consumer dungeon/func_80DBA620. */
const u32 blume_slot_g_behavior_targets[12] __attribute__((aligned(4))) = {
    (u32)((u8 *)update_actor_dungeon_behavior_and_animation + 0x3E4),
    (u32)((u8 *)update_actor_dungeon_behavior_and_animation + 0x3E4),
    (u32)((u8 *)update_actor_dungeon_behavior_and_animation + 0x3E4),
    (u32)((u8 *)update_actor_dungeon_behavior_and_animation + 0x410),
    (u32)((u8 *)update_actor_dungeon_behavior_and_animation + 0x390),
    (u32)((u8 *)update_actor_dungeon_behavior_and_animation + 0x390),
    (u32)((u8 *)update_actor_dungeon_behavior_and_animation + 0x390),
    (u32)((u8 *)update_actor_dungeon_behavior_and_animation + 0x33C),
    (u32)((u8 *)update_actor_dungeon_behavior_and_animation + 0x374),
    (u32)((u8 *)update_actor_dungeon_behavior_and_animation + 0x410),
    (u32)((u8 *)update_actor_dungeon_behavior_and_animation + 0x410),
    (u32)((u8 *)update_actor_dungeon_behavior_and_animation + 0x3D4)
};
