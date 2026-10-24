#include "common.h"

extern void update_dungeon_action_behavior_facing_animation_state(void);

/* jump_table; owner: dungeon/func_80EA38F4. */
const void *const picket_slot_c_behavior_targets[12] __attribute__((aligned(4))) = {
    ((u8 *)update_dungeon_action_behavior_facing_animation_state + 0x410),
    ((u8 *)update_dungeon_action_behavior_facing_animation_state + 0x410),
    ((u8 *)update_dungeon_action_behavior_facing_animation_state + 0x410),
    ((u8 *)update_dungeon_action_behavior_facing_animation_state + 0x43C),
    ((u8 *)update_dungeon_action_behavior_facing_animation_state + 0x3BC),
    ((u8 *)update_dungeon_action_behavior_facing_animation_state + 0x3BC),
    ((u8 *)update_dungeon_action_behavior_facing_animation_state + 0x3BC),
    ((u8 *)update_dungeon_action_behavior_facing_animation_state + 0x33C),
    ((u8 *)update_dungeon_action_behavior_facing_animation_state + 0x390),
    ((u8 *)update_dungeon_action_behavior_facing_animation_state + 0x374),
    ((u8 *)update_dungeon_action_behavior_facing_animation_state + 0x43C),
    ((u8 *)update_dungeon_action_behavior_facing_animation_state + 0x400)
};
