#include "common.h"

extern void advance_actor_action_and_completion(void);

/* jump_table; owner: dungeon/func_8128ED6C. */
const void *const D_8015D838[9] __attribute__((aligned(4))) = {
    ((u8 *)advance_actor_action_and_completion + 0x64),
    ((u8 *)advance_actor_action_and_completion + 0x2A8),
    ((u8 *)advance_actor_action_and_completion + 0x2F0),
    ((u8 *)advance_actor_action_and_completion + 0x330),
    ((u8 *)advance_actor_action_and_completion + 0x3D0),
    ((u8 *)advance_actor_action_and_completion + 0x43C),
    ((u8 *)advance_actor_action_and_completion + 0x4A4),
    ((u8 *)advance_actor_action_and_completion + 0x4C4),
    ((u8 *)advance_actor_action_and_completion + 0x558)
};
