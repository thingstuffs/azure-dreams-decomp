#include "common.h"

extern void update_actor_item_action(void);

/* jump_table; owner: dungeon/func_80F05FB0. */
const u32 D_8014C8A0[7] __attribute__((aligned(4))) = {
    (u32)((u8 *)update_actor_item_action + 0x110),
    (u32)((u8 *)update_actor_item_action + 0x108),
    (u32)((u8 *)update_actor_item_action + 0x100),
    (u32)((u8 *)update_actor_item_action + 0x118),
    (u32)((u8 *)update_actor_item_action + 0xBC),
    (u32)((u8 *)update_actor_item_action + 0xB4),
    (u32)((u8 *)update_actor_item_action + 0xAC)
};
