#include "common.h"

extern void update_actor_movement_animation_and_facing(void);

/* jump_table; owner: dungeon/func_80F2D774. */
const u32 stealth_slot_a_behavior_targets[12] __attribute__((aligned(4))) = {
    (u32)((u8 *)update_actor_movement_animation_and_facing + 0x3E4),
    (u32)((u8 *)update_actor_movement_animation_and_facing + 0x3E4),
    (u32)((u8 *)update_actor_movement_animation_and_facing + 0x3E4),
    (u32)((u8 *)update_actor_movement_animation_and_facing + 0x410),
    (u32)((u8 *)update_actor_movement_animation_and_facing + 0x390),
    (u32)((u8 *)update_actor_movement_animation_and_facing + 0x390),
    (u32)((u8 *)update_actor_movement_animation_and_facing + 0x390),
    (u32)((u8 *)update_actor_movement_animation_and_facing + 0x33C),
    (u32)((u8 *)update_actor_movement_animation_and_facing + 0x374),
    (u32)((u8 *)update_actor_movement_animation_and_facing + 0x410),
    (u32)((u8 *)update_actor_movement_animation_and_facing + 0x410),
    (u32)((u8 *)update_actor_movement_animation_and_facing + 0x3D4)
};
