#include "common.h"

extern void update_actor_action_fourth(void);

/* jump_table; owner: dungeon/func_80A35684. */
const u32 D_80158808[12] __attribute__((aligned(4))) = {
    (u32)((u8 *)update_actor_action_fourth + 0x3C8),
    (u32)((u8 *)update_actor_action_fourth + 0x3C8),
    (u32)((u8 *)update_actor_action_fourth + 0x3C8),
    (u32)((u8 *)update_actor_action_fourth + 0x3F4),
    (u32)((u8 *)update_actor_action_fourth + 0x374),
    (u32)((u8 *)update_actor_action_fourth + 0x374),
    (u32)((u8 *)update_actor_action_fourth + 0x374),
    (u32)((u8 *)update_actor_action_fourth + 0x33C),
    (u32)((u8 *)update_actor_action_fourth + 0x33C),
    (u32)((u8 *)update_actor_action_fourth + 0x3F4),
    (u32)((u8 *)update_actor_action_fourth + 0x3F4),
    (u32)((u8 *)update_actor_action_fourth + 0x3B8)
};
