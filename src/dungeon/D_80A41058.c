#include "common.h"

extern void advance_actor_ability_action_and_effects(void);

/* jump_table; owner: dungeon/func_80A430C4. */
const u32 D_8014C858[7] __attribute__((aligned(4))) = {
    (u32)((u8 *)advance_actor_ability_action_and_effects + 0x128),
    (u32)((u8 *)advance_actor_ability_action_and_effects + 0x120),
    (u32)((u8 *)advance_actor_ability_action_and_effects + 0x118),
    (u32)((u8 *)advance_actor_ability_action_and_effects + 0x130),
    (u32)((u8 *)advance_actor_ability_action_and_effects + 0xD8),
    (u32)((u8 *)advance_actor_ability_action_and_effects + 0xD0),
    (u32)((u8 *)advance_actor_ability_action_and_effects + 0xC8)
};
