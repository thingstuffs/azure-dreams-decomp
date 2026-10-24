#include "common.h"

extern void update_actor_behavior_variant_f(void);

/* jump_table; owner: dungeon/func_80A2F684. */
const void *const ifrit_slot_d_behavior_targets[12] __attribute__((aligned(4))) = {
    ((u8 *)update_actor_behavior_variant_f + 0x3C8),
    ((u8 *)update_actor_behavior_variant_f + 0x3C8),
    ((u8 *)update_actor_behavior_variant_f + 0x3C8),
    ((u8 *)update_actor_behavior_variant_f + 0x3F4),
    ((u8 *)update_actor_behavior_variant_f + 0x374),
    ((u8 *)update_actor_behavior_variant_f + 0x374),
    ((u8 *)update_actor_behavior_variant_f + 0x374),
    ((u8 *)update_actor_behavior_variant_f + 0x33C),
    ((u8 *)update_actor_behavior_variant_f + 0x33C),
    ((u8 *)update_actor_behavior_variant_f + 0x3F4),
    ((u8 *)update_actor_behavior_variant_f + 0x3F4),
    ((u8 *)update_actor_behavior_variant_f + 0x3B8)
};
