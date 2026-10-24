#include "common.h"

extern void update_actor_behavior_fourth(void);

/* jump_table; owner: dungeon/func_80A370C4. */
const void *const D_80158858[7] __attribute__((aligned(4))) = {
    ((u8 *)update_actor_behavior_fourth + 0x128),
    ((u8 *)update_actor_behavior_fourth + 0x120),
    ((u8 *)update_actor_behavior_fourth + 0x118),
    ((u8 *)update_actor_behavior_fourth + 0x130),
    ((u8 *)update_actor_behavior_fourth + 0xD8),
    ((u8 *)update_actor_behavior_fourth + 0xD0),
    ((u8 *)update_actor_behavior_fourth + 0xC8)
};
