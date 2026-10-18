#include "common.h"

extern void update_actor_actions_and_impact_effects(void);

/* jump_table; owner: dungeon/func_80A1F0C4. */
const u32 D_80170858[7] __attribute__((aligned(4))) = {
    (u32)((u8 *)update_actor_actions_and_impact_effects + 0x128),
    (u32)((u8 *)update_actor_actions_and_impact_effects + 0x120),
    (u32)((u8 *)update_actor_actions_and_impact_effects + 0x118),
    (u32)((u8 *)update_actor_actions_and_impact_effects + 0x130),
    (u32)((u8 *)update_actor_actions_and_impact_effects + 0xD8),
    (u32)((u8 *)update_actor_actions_and_impact_effects + 0xD0),
    (u32)((u8 *)update_actor_actions_and_impact_effects + 0xC8)
};
