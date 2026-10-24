#include "common.h"

extern void update_entity_action(void);

/* jump_table; owner: dungeon/func_80FED6A8. */
const void *const killer_slot_d_behavior_targets[12] __attribute__((aligned(4))) = {
    ((u8 *)update_entity_action + 0x410),
    ((u8 *)update_entity_action + 0x410),
    ((u8 *)update_entity_action + 0x410),
    ((u8 *)update_entity_action + 0x43C),
    ((u8 *)update_entity_action + 0x3BC),
    ((u8 *)update_entity_action + 0x3BC),
    ((u8 *)update_entity_action + 0x3BC),
    ((u8 *)update_entity_action + 0x34C),
    ((u8 *)update_entity_action + 0x33C),
    ((u8 *)update_entity_action + 0x43C),
    ((u8 *)update_entity_action + 0x43C),
    ((u8 *)update_entity_action + 0x400)
};
