#include "common.h"

extern void update_action_behavior_facing_and_animation(void);

/* jump_table; owner: dungeon/func_80E918F4. */
const u32 picket_slot_f_behavior_targets[12] __attribute__((aligned(4))) = {
    (u32)((u8 *)update_action_behavior_facing_and_animation + 0x410),
    (u32)((u8 *)update_action_behavior_facing_and_animation + 0x410),
    (u32)((u8 *)update_action_behavior_facing_and_animation + 0x410),
    (u32)((u8 *)update_action_behavior_facing_and_animation + 0x43C),
    (u32)((u8 *)update_action_behavior_facing_and_animation + 0x3BC),
    (u32)((u8 *)update_action_behavior_facing_and_animation + 0x3BC),
    (u32)((u8 *)update_action_behavior_facing_and_animation + 0x3BC),
    (u32)((u8 *)update_action_behavior_facing_and_animation + 0x33C),
    (u32)((u8 *)update_action_behavior_facing_and_animation + 0x390),
    (u32)((u8 *)update_action_behavior_facing_and_animation + 0x374),
    (u32)((u8 *)update_action_behavior_facing_and_animation + 0x43C),
    (u32)((u8 *)update_action_behavior_facing_and_animation + 0x400)
};
