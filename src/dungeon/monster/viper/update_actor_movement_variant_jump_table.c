#include "common.h"

extern void update_actor_movement_variant(void);

/* jump_table; owner: dungeon/func_80F45694. */
const void *const viper_slot_d_behavior_targets[12] __attribute__((aligned(4))) = {
    ((u8 *)update_actor_movement_variant + 0x3E4),
    ((u8 *)update_actor_movement_variant + 0x3E4),
    ((u8 *)update_actor_movement_variant + 0x3E4),
    ((u8 *)update_actor_movement_variant + 0x410),
    ((u8 *)update_actor_movement_variant + 0x390),
    ((u8 *)update_actor_movement_variant + 0x390),
    ((u8 *)update_actor_movement_variant + 0x390),
    ((u8 *)update_actor_movement_variant + 0x33C),
    ((u8 *)update_actor_movement_variant + 0x374),
    ((u8 *)update_actor_movement_variant + 0x410),
    ((u8 *)update_actor_movement_variant + 0x410),
    ((u8 *)update_actor_movement_variant + 0x3D4)
};
