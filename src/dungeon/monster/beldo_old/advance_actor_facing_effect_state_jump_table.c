#include "common.h"

extern void advance_actor_facing_effect_state(void);

/* jump_table; owner: dungeon/func_8128F6C4. */
const void *const D_8015D880[6] __attribute__((aligned(4))) = {
    ((u8 *)advance_actor_facing_effect_state + 0x5C),
    ((u8 *)advance_actor_facing_effect_state + 0xCC),
    ((u8 *)advance_actor_facing_effect_state + 0xE4),
    ((u8 *)advance_actor_facing_effect_state + 0x110),
    ((u8 *)advance_actor_facing_effect_state + 0x38C),
    ((u8 *)advance_actor_facing_effect_state + 0x3FC)
};
