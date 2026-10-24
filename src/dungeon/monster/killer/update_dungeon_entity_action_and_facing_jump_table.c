#include "common.h"

extern void update_dungeon_entity_action_and_facing(void);

/* jump_table; owner: dungeon/func_80FE16A8. */
const void *const killer_slot_f_behavior_targets[12] __attribute__((aligned(4))) = {
    ((u8 *)update_dungeon_entity_action_and_facing + 0x410),
    ((u8 *)update_dungeon_entity_action_and_facing + 0x410),
    ((u8 *)update_dungeon_entity_action_and_facing + 0x410),
    ((u8 *)update_dungeon_entity_action_and_facing + 0x43C),
    ((u8 *)update_dungeon_entity_action_and_facing + 0x3BC),
    ((u8 *)update_dungeon_entity_action_and_facing + 0x3BC),
    ((u8 *)update_dungeon_entity_action_and_facing + 0x3BC),
    ((u8 *)update_dungeon_entity_action_and_facing + 0x34C),
    ((u8 *)update_dungeon_entity_action_and_facing + 0x33C),
    ((u8 *)update_dungeon_entity_action_and_facing + 0x43C),
    ((u8 *)update_dungeon_entity_action_and_facing + 0x43C),
    ((u8 *)update_dungeon_entity_action_and_facing + 0x400)
};
