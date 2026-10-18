#include "common.h"

extern void update_entity_action(void);

/* jump_table; owner: dungeon/func_80FED6A8. */
const u32 D_8015E808[12] __attribute__((aligned(4))) = {
    (u32)((u8 *)update_entity_action + 0x410),
    (u32)((u8 *)update_entity_action + 0x410),
    (u32)((u8 *)update_entity_action + 0x410),
    (u32)((u8 *)update_entity_action + 0x43C),
    (u32)((u8 *)update_entity_action + 0x3BC),
    (u32)((u8 *)update_entity_action + 0x3BC),
    (u32)((u8 *)update_entity_action + 0x3BC),
    (u32)((u8 *)update_entity_action + 0x34C),
    (u32)((u8 *)update_entity_action + 0x33C),
    (u32)((u8 *)update_entity_action + 0x43C),
    (u32)((u8 *)update_entity_action + 0x43C),
    (u32)((u8 *)update_entity_action + 0x400)
};
