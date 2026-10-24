#include "common.h"

extern void update_dungeon_action_behavior(void);

/* jump_table; owner: dungeon/func_80EAF8F4. */
const void *const picket_slot_a_behavior_targets[12] __attribute__((aligned(4))) = {
    ((u8 *)update_dungeon_action_behavior + 0x410),
    ((u8 *)update_dungeon_action_behavior + 0x410),
    ((u8 *)update_dungeon_action_behavior + 0x410),
    ((u8 *)update_dungeon_action_behavior + 0x43C),
    ((u8 *)update_dungeon_action_behavior + 0x3BC),
    ((u8 *)update_dungeon_action_behavior + 0x3BC),
    ((u8 *)update_dungeon_action_behavior + 0x3BC),
    ((u8 *)update_dungeon_action_behavior + 0x33C),
    ((u8 *)update_dungeon_action_behavior + 0x390),
    ((u8 *)update_dungeon_action_behavior + 0x374),
    ((u8 *)update_dungeon_action_behavior + 0x43C),
    ((u8 *)update_dungeon_action_behavior + 0x400)
};
