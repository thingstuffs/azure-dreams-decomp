#include "common.h"

extern void advance_actor_facing_effects(void);

/* jump_table; owner: dungeon/func_812536C4. */
const void *const D_80170880[6] __attribute__((aligned(4))) = {
    ((u8 *)advance_actor_facing_effects + 0x5C),
    ((u8 *)advance_actor_facing_effects + 0xCC),
    ((u8 *)advance_actor_facing_effects + 0xE4),
    ((u8 *)advance_actor_facing_effects + 0x110),
    ((u8 *)advance_actor_facing_effects + 0x38C),
    ((u8 *)advance_actor_facing_effects + 0x3FC)
};
