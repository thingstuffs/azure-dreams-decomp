#include "common.h"

extern void advance_actor_facing_effect_state(void);

/* jump_table; owner: dungeon/func_8128F6C4. */
const u32 D_8015D880[6] __attribute__((aligned(4))) = {
    (u32)((u8 *)advance_actor_facing_effect_state + 0x5C),
    (u32)((u8 *)advance_actor_facing_effect_state + 0xCC),
    (u32)((u8 *)advance_actor_facing_effect_state + 0xE4),
    (u32)((u8 *)advance_actor_facing_effect_state + 0x110),
    (u32)((u8 *)advance_actor_facing_effect_state + 0x38C),
    (u32)((u8 *)advance_actor_facing_effect_state + 0x3FC)
};
