#include "common.h"

extern void update_actor_ability_action_and_effects(void);

/* jump_table; owner: dungeon/func_80FA7240. */
const void *const D_80152838[7] __attribute__((aligned(4))) = {
    ((u8 *)update_actor_ability_action_and_effects + 0x11C),
    ((u8 *)update_actor_ability_action_and_effects + 0x114),
    ((u8 *)update_actor_ability_action_and_effects + 0x10C),
    ((u8 *)update_actor_ability_action_and_effects + 0x124),
    ((u8 *)update_actor_ability_action_and_effects + 0xCC),
    ((u8 *)update_actor_ability_action_and_effects + 0xC4),
    ((u8 *)update_actor_ability_action_and_effects + 0xBC)
};
