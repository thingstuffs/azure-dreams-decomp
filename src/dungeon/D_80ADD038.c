#include "common.h"

extern void advance_actor_action_sequence(void);

/* jump_table; owner: dungeon/func_80ADF7D8. */
const u32 D_80158838[5] __attribute__((aligned(4))) = {
    (u32)((u8 *)advance_actor_action_sequence + 0x48),
    (u32)((u8 *)advance_actor_action_sequence + 0x98),
    (u32)((u8 *)advance_actor_action_sequence + 0x10C),
    (u32)((u8 *)advance_actor_action_sequence + 0x180),
    (u32)((u8 *)advance_actor_action_sequence + 0x1F8)
};
