#include "common.h"

extern void update_actor_ability_action_2(void);

/* jump_table; owner: dungeon/func_80EF9FB0. */
const void *const D_80158888[5] __attribute__((aligned(4))) = {
    ((u8 *)update_actor_ability_action_2 + 0x60),
    ((u8 *)update_actor_ability_action_2 + 0x298),
    ((u8 *)update_actor_ability_action_2 + 0x2E0),
    ((u8 *)update_actor_ability_action_2 + 0x434),
    ((u8 *)update_actor_ability_action_2 + 0x448)
};
