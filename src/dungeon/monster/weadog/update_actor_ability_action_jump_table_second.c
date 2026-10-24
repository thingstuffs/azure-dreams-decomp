#include "common.h"

extern void update_actor_ability_action_2(void);

/* jump_table; owner: dungeon/func_80EF9FB0. */
const void *const D_801588A0[7] __attribute__((aligned(4))) = {
    ((u8 *)update_actor_ability_action_2 + 0x110),
    ((u8 *)update_actor_ability_action_2 + 0x108),
    ((u8 *)update_actor_ability_action_2 + 0x100),
    ((u8 *)update_actor_ability_action_2 + 0x118),
    ((u8 *)update_actor_ability_action_2 + 0xBC),
    ((u8 *)update_actor_ability_action_2 + 0xB4),
    ((u8 *)update_actor_ability_action_2 + 0xAC)
};
