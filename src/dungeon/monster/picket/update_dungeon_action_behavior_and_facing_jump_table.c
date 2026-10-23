#include "common.h"

extern void update_dungeon_action_behavior_and_facing(void);

/* jump_table; owner: dungeon/func_80E9D8F4. */
const u32 picket_slot_d_behavior_targets[12] __attribute__((aligned(4))) = {
    (u32)((u8 *)update_dungeon_action_behavior_and_facing + 0x410),
    (u32)((u8 *)update_dungeon_action_behavior_and_facing + 0x410),
    (u32)((u8 *)update_dungeon_action_behavior_and_facing + 0x410),
    (u32)((u8 *)update_dungeon_action_behavior_and_facing + 0x43C),
    (u32)((u8 *)update_dungeon_action_behavior_and_facing + 0x3BC),
    (u32)((u8 *)update_dungeon_action_behavior_and_facing + 0x3BC),
    (u32)((u8 *)update_dungeon_action_behavior_and_facing + 0x3BC),
    (u32)((u8 *)update_dungeon_action_behavior_and_facing + 0x33C),
    (u32)((u8 *)update_dungeon_action_behavior_and_facing + 0x390),
    (u32)((u8 *)update_dungeon_action_behavior_and_facing + 0x374),
    (u32)((u8 *)update_dungeon_action_behavior_and_facing + 0x43C),
    (u32)((u8 *)update_dungeon_action_behavior_and_facing + 0x400)
};
