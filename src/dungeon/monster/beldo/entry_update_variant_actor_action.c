#include "common.h"

extern void update_variant_actor_action(void);

/* jump_table; owner: dungeon/func_81269D14. */
const void *const beldo_slot_c_behavior_targets[12] __attribute__((aligned(4))) = {
    ((u8 *)update_variant_actor_action + 0x3AC),
    ((u8 *)update_variant_actor_action + 0x3AC),
    ((u8 *)update_variant_actor_action + 0x3AC),
    ((u8 *)update_variant_actor_action + 0x3D4),
    ((u8 *)update_variant_actor_action + 0x380),
    ((u8 *)update_variant_actor_action + 0x380),
    ((u8 *)update_variant_actor_action + 0x380),
    ((u8 *)update_variant_actor_action + 0x380),
    ((u8 *)update_variant_actor_action + 0x380),
    ((u8 *)update_variant_actor_action + 0x3D4),
    ((u8 *)update_variant_actor_action + 0x3D4),
    ((u8 *)update_variant_actor_action + 0x370)
};
