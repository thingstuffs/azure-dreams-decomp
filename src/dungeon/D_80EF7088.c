#include "common.h"

extern void update_actor_ability_action_2(void);

/* jump_table; owner: dungeon/func_80EF9FB0. */
const u32 D_80158888[5] __attribute__((aligned(4))) = {
    (u32)((u8 *)update_actor_ability_action_2 + 0x60),
    (u32)((u8 *)update_actor_ability_action_2 + 0x298),
    (u32)((u8 *)update_actor_ability_action_2 + 0x2E0),
    (u32)((u8 *)update_actor_ability_action_2 + 0x434),
    (u32)((u8 *)update_actor_ability_action_2 + 0x448)
};
