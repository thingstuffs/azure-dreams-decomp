#include "common.h"

extern void update_entity_action_facing_alt(void);

/* jump_table; owner: dungeon/func_80FFF6A8. */
const void *const killer_slot_a_behavior_targets[12] __attribute__((aligned(4))) = {
    ((u8 *)update_entity_action_facing_alt + 0x410),
    ((u8 *)update_entity_action_facing_alt + 0x410),
    ((u8 *)update_entity_action_facing_alt + 0x410),
    ((u8 *)update_entity_action_facing_alt + 0x43C),
    ((u8 *)update_entity_action_facing_alt + 0x3BC),
    ((u8 *)update_entity_action_facing_alt + 0x3BC),
    ((u8 *)update_entity_action_facing_alt + 0x3BC),
    ((u8 *)update_entity_action_facing_alt + 0x34C),
    ((u8 *)update_entity_action_facing_alt + 0x33C),
    ((u8 *)update_entity_action_facing_alt + 0x43C),
    ((u8 *)update_entity_action_facing_alt + 0x43C),
    ((u8 *)update_entity_action_facing_alt + 0x400)
};
