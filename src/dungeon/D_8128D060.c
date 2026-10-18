#include "common.h"

extern void advance_actor_action_and_completion(void);

/* jump_table; owner: dungeon/func_8128ED6C. */
const u32 D_8015D860[7] __attribute__((aligned(4))) = {
    (u32)((u8 *)advance_actor_action_and_completion + 0x114),
    (u32)((u8 *)advance_actor_action_and_completion + 0x10C),
    (u32)((u8 *)advance_actor_action_and_completion + 0x104),
    (u32)((u8 *)advance_actor_action_and_completion + 0x11C),
    (u32)((u8 *)advance_actor_action_and_completion + 0xC0),
    (u32)((u8 *)advance_actor_action_and_completion + 0xB8),
    (u32)((u8 *)advance_actor_action_and_completion + 0xB0)
};
