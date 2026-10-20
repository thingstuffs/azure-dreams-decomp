#include "common.h"

extern void advance_actor_action_variant_c(void);

/* jump_table; owner: dungeon/func_80EF3FB0. */
const u32 D_8015E888[5] __attribute__((aligned(4))) = {
    (u32)((u8 *)advance_actor_action_variant_c + 0x60),
    (u32)((u8 *)advance_actor_action_variant_c + 0x298),
    (u32)((u8 *)advance_actor_action_variant_c + 0x2E0),
    (u32)((u8 *)advance_actor_action_variant_c + 0x434),
    (u32)((u8 *)advance_actor_action_variant_c + 0x448)
};
