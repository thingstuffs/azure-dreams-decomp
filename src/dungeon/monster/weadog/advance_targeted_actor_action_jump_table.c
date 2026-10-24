#include "common.h"

extern void advance_targeted_actor_action(void);

/* jump_table; owner: dungeon/func_80EE7FB0. */
const void *const D_8016A888[5] __attribute__((aligned(4))) = {
    ((u8 *)advance_targeted_actor_action + 0x60),
    ((u8 *)advance_targeted_actor_action + 0x298),
    ((u8 *)advance_targeted_actor_action + 0x2E0),
    ((u8 *)advance_targeted_actor_action + 0x434),
    ((u8 *)advance_targeted_actor_action + 0x448)
};
