#include "common.h"

extern void update_dungeon_item_action(void);

/* jump_table; owner: dungeon/func_80A250C4. */
const u32 ifrit_slot_f_action_cases[7] __attribute__((aligned(4))) = {
    (u32)((u8 *)update_dungeon_item_action + 0x128),
    (u32)((u8 *)update_dungeon_item_action + 0x120),
    (u32)((u8 *)update_dungeon_item_action + 0x118),
    (u32)((u8 *)update_dungeon_item_action + 0x130),
    (u32)((u8 *)update_dungeon_item_action + 0xD8),
    (u32)((u8 *)update_dungeon_item_action + 0xD0),
    (u32)((u8 *)update_dungeon_item_action + 0xC8)
};
