#include "common.h"

extern void advance_actor_action_variant_c(void);

/* jump_table; owner: dungeon/func_80EF3FB0. */
const u32 D_8015E8A0[7] __attribute__((aligned(4))) = {
    (u32)((u8 *)advance_actor_action_variant_c + 0x110),
    (u32)((u8 *)advance_actor_action_variant_c + 0x108),
    (u32)((u8 *)advance_actor_action_variant_c + 0x100),
    (u32)((u8 *)advance_actor_action_variant_c + 0x118),
    (u32)((u8 *)advance_actor_action_variant_c + 0xBC),
    (u32)((u8 *)advance_actor_action_variant_c + 0xB4),
    (u32)((u8 *)advance_actor_action_variant_c + 0xAC)
};
