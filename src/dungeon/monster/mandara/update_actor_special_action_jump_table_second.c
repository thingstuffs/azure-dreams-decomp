#include "common.h"

extern void update_actor_special_action(void);

/* jump_table; owner: dungeon/func_80FC976C. */
const void *const D_80158820[12] __attribute__((aligned(4))) = {
    ((u8 *)update_actor_special_action + 0x828),
    ((u8 *)update_actor_special_action + 0x828),
    ((u8 *)update_actor_special_action + 0x828),
    ((u8 *)update_actor_special_action + 0x854),
    ((u8 *)update_actor_special_action + 0x7D4),
    ((u8 *)update_actor_special_action + 0x7D4),
    ((u8 *)update_actor_special_action + 0x7D4),
    ((u8 *)update_actor_special_action + 0x76C),
    ((u8 *)update_actor_special_action + 0x76C),
    ((u8 *)update_actor_special_action + 0x854),
    ((u8 *)update_actor_special_action + 0x854),
    ((u8 *)update_actor_special_action + 0x818)
};
