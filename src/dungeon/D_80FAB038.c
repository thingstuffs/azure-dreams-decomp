#include "common.h"

extern void update_actor_item_target_action(void);

/* jump_table; owner: dungeon/func_80FAD240. */
const u32 D_8014C838[7] __attribute__((aligned(4))) = {
    (u32)((u8 *)update_actor_item_target_action + 0x11C),
    (u32)((u8 *)update_actor_item_target_action + 0x114),
    (u32)((u8 *)update_actor_item_target_action + 0x10C),
    (u32)((u8 *)update_actor_item_target_action + 0x124),
    (u32)((u8 *)update_actor_item_target_action + 0xCC),
    (u32)((u8 *)update_actor_item_target_action + 0xC4),
    (u32)((u8 *)update_actor_item_target_action + 0xBC)
};
