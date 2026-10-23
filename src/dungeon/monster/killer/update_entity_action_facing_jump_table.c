#include "common.h"

extern void update_entity_action_facing(void);

/* Exact jump_table span; dispatch consumer dungeon/func_80FDB6A8. */
const u32 killer_slot_g_behavior_targets[12] __attribute__((aligned(4))) = {
    (u32)((u8 *)update_entity_action_facing + 0x410),
    (u32)((u8 *)update_entity_action_facing + 0x410),
    (u32)((u8 *)update_entity_action_facing + 0x410),
    (u32)((u8 *)update_entity_action_facing + 0x43C),
    (u32)((u8 *)update_entity_action_facing + 0x3BC),
    (u32)((u8 *)update_entity_action_facing + 0x3BC),
    (u32)((u8 *)update_entity_action_facing + 0x3BC),
    (u32)((u8 *)update_entity_action_facing + 0x34C),
    (u32)((u8 *)update_entity_action_facing + 0x33C),
    (u32)((u8 *)update_entity_action_facing + 0x43C),
    (u32)((u8 *)update_entity_action_facing + 0x43C),
    (u32)((u8 *)update_entity_action_facing + 0x400)
};
