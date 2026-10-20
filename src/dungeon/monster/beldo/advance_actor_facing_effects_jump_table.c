#include "common.h"

extern void advance_actor_facing_effects(void);

/* jump_table; owner: dungeon/func_812536C4. */
const u32 D_80170880[6] __attribute__((aligned(4))) = {
    (u32)((u8 *)advance_actor_facing_effects + 0x5C),
    (u32)((u8 *)advance_actor_facing_effects + 0xCC),
    (u32)((u8 *)advance_actor_facing_effects + 0xE4),
    (u32)((u8 *)advance_actor_facing_effects + 0x110),
    (u32)((u8 *)advance_actor_facing_effects + 0x38C),
    (u32)((u8 *)advance_actor_facing_effects + 0x3FC)
};
