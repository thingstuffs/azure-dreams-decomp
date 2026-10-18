#include "common.h"

extern void update_actor_behavior_variant_f(void);

/* jump_table; owner: dungeon/func_80A2F684. */
const u32 D_8015E808[12] __attribute__((aligned(4))) = {
    (u32)((u8 *)update_actor_behavior_variant_f + 0x3C8),
    (u32)((u8 *)update_actor_behavior_variant_f + 0x3C8),
    (u32)((u8 *)update_actor_behavior_variant_f + 0x3C8),
    (u32)((u8 *)update_actor_behavior_variant_f + 0x3F4),
    (u32)((u8 *)update_actor_behavior_variant_f + 0x374),
    (u32)((u8 *)update_actor_behavior_variant_f + 0x374),
    (u32)((u8 *)update_actor_behavior_variant_f + 0x374),
    (u32)((u8 *)update_actor_behavior_variant_f + 0x33C),
    (u32)((u8 *)update_actor_behavior_variant_f + 0x33C),
    (u32)((u8 *)update_actor_behavior_variant_f + 0x3F4),
    (u32)((u8 *)update_actor_behavior_variant_f + 0x3F4),
    (u32)((u8 *)update_actor_behavior_variant_f + 0x3B8)
};
