#include "common.h"

extern void advance_actor_action_variant_c(void);

/* jump_table; owner: dungeon/func_80EF3FB0. */
const void *const D_8015E888[5] __attribute__((aligned(4))) = {
    ((u8 *)advance_actor_action_variant_c + 0x60),
    ((u8 *)advance_actor_action_variant_c + 0x298),
    ((u8 *)advance_actor_action_variant_c + 0x2E0),
    ((u8 *)advance_actor_action_variant_c + 0x434),
    ((u8 *)advance_actor_action_variant_c + 0x448)
};
