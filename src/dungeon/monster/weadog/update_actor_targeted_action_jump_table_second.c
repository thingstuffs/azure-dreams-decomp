#include "common.h"

extern void update_actor_targeted_action(void);

/* jump_table; owner: dungeon/func_80EE1FB0. */
const void *const D_801708A0[7] __attribute__((aligned(4))) = {
    ((u8 *)update_actor_targeted_action + 0x110),
    ((u8 *)update_actor_targeted_action + 0x108),
    ((u8 *)update_actor_targeted_action + 0x100),
    ((u8 *)update_actor_targeted_action + 0x118),
    ((u8 *)update_actor_targeted_action + 0xBC),
    ((u8 *)update_actor_targeted_action + 0xB4),
    ((u8 *)update_actor_targeted_action + 0xAC)
};
