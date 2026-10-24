#include "common.h"

extern void advance_actor_action_variant_a(void);

/* jump_table; owner: dungeon/func_80EF3D14. */
const void *const D_8015E870[5] __attribute__((aligned(4))) = {
    ((u8 *)advance_actor_action_variant_a + 0x48),
    ((u8 *)advance_actor_action_variant_a + 0xD4),
    ((u8 *)advance_actor_action_variant_a + 0x118),
    ((u8 *)advance_actor_action_variant_a + 0x178),
    ((u8 *)advance_actor_action_variant_a + 0x23C)
};
