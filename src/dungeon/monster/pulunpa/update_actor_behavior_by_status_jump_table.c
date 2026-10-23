#include "common.h"

extern void update_actor_behavior_by_status(void);

/* jump_table; owner: dungeon/func_80CBD720. */
const u32 pulunpa_slot_g_behavior_targets[12] __attribute__((aligned(4))) = {
    (u32)((u8 *)update_actor_behavior_by_status + 0x3C8),
    (u32)((u8 *)update_actor_behavior_by_status + 0x3C8),
    (u32)((u8 *)update_actor_behavior_by_status + 0x3C8),
    (u32)((u8 *)update_actor_behavior_by_status + 0x3F4),
    (u32)((u8 *)update_actor_behavior_by_status + 0x374),
    (u32)((u8 *)update_actor_behavior_by_status + 0x374),
    (u32)((u8 *)update_actor_behavior_by_status + 0x374),
    (u32)((u8 *)update_actor_behavior_by_status + 0x33C),
    (u32)((u8 *)update_actor_behavior_by_status + 0x33C),
    (u32)((u8 *)update_actor_behavior_by_status + 0x3F4),
    (u32)((u8 *)update_actor_behavior_by_status + 0x3F4),
    (u32)((u8 *)update_actor_behavior_by_status + 0x3B8)
};
