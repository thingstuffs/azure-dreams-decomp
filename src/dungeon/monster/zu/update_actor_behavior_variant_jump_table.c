#include "common.h"

extern void update_actor_behavior_variant_e(void);

/* jump_table; owner: dungeon/func_80F9F938. */
const u32 zu_slot_c_behavior_targets[12] __attribute__((aligned(4))) = {
    (u32)((u8 *)update_actor_behavior_variant_e + 0x434),
    (u32)((u8 *)update_actor_behavior_variant_e + 0x434),
    (u32)((u8 *)update_actor_behavior_variant_e + 0x434),
    (u32)((u8 *)update_actor_behavior_variant_e + 0x460),
    (u32)((u8 *)update_actor_behavior_variant_e + 0x3E0),
    (u32)((u8 *)update_actor_behavior_variant_e + 0x3E0),
    (u32)((u8 *)update_actor_behavior_variant_e + 0x3E0),
    (u32)((u8 *)update_actor_behavior_variant_e + 0x3A8),
    (u32)((u8 *)update_actor_behavior_variant_e + 0x38C),
    (u32)((u8 *)update_actor_behavior_variant_e + 0x460),
    (u32)((u8 *)update_actor_behavior_variant_e + 0x460),
    (u32)((u8 *)update_actor_behavior_variant_e + 0x424)
};
