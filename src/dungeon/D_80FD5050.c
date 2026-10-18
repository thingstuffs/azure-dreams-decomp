#include "common.h"

extern void advance_actor_item_action_and_recovery(void);

/* jump_table; owner: dungeon/func_80FD75EC. */
const u32 D_8014C850[7] __attribute__((aligned(4))) = {
    (u32)((u8 *)advance_actor_item_action_and_recovery + 0x11C),
    (u32)((u8 *)advance_actor_item_action_and_recovery + 0x114),
    (u32)((u8 *)advance_actor_item_action_and_recovery + 0x10C),
    (u32)((u8 *)advance_actor_item_action_and_recovery + 0x124),
    (u32)((u8 *)advance_actor_item_action_and_recovery + 0xCC),
    (u32)((u8 *)advance_actor_item_action_and_recovery + 0xC4),
    (u32)((u8 *)advance_actor_item_action_and_recovery + 0xBC)
};
