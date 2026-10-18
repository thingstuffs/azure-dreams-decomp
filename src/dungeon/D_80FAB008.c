#include "common.h"

extern void update_actor_action_and_facing(void);

/* jump_table; owner: dungeon/func_80FAB938. */
const u32 D_8014C808[12] __attribute__((aligned(4))) = {
    (u32)((u8 *)update_actor_action_and_facing + 0x434),
    (u32)((u8 *)update_actor_action_and_facing + 0x434),
    (u32)((u8 *)update_actor_action_and_facing + 0x434),
    (u32)((u8 *)update_actor_action_and_facing + 0x460),
    (u32)((u8 *)update_actor_action_and_facing + 0x3E0),
    (u32)((u8 *)update_actor_action_and_facing + 0x3E0),
    (u32)((u8 *)update_actor_action_and_facing + 0x3E0),
    (u32)((u8 *)update_actor_action_and_facing + 0x3A8),
    (u32)((u8 *)update_actor_action_and_facing + 0x38C),
    (u32)((u8 *)update_actor_action_and_facing + 0x460),
    (u32)((u8 *)update_actor_action_and_facing + 0x460),
    (u32)((u8 *)update_actor_action_and_facing + 0x424)
};
