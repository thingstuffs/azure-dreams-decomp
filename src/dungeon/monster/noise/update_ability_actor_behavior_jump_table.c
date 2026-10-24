#include "common.h"

extern void update_ability_actor_behavior(void);

/* jump_table; owner: dungeon/func_80D29F60. */
const void *const noise_slot_c_behavior_targets[12] __attribute__((aligned(4))) = {
    ((u8 *)update_ability_actor_behavior + 0x3F8),
    ((u8 *)update_ability_actor_behavior + 0x3F8),
    ((u8 *)update_ability_actor_behavior + 0x3F8),
    ((u8 *)update_ability_actor_behavior + 0x424),
    ((u8 *)update_ability_actor_behavior + 0x3A4),
    ((u8 *)update_ability_actor_behavior + 0x3A4),
    ((u8 *)update_ability_actor_behavior + 0x3A4),
    ((u8 *)update_ability_actor_behavior + 0x350),
    ((u8 *)update_ability_actor_behavior + 0x388),
    ((u8 *)update_ability_actor_behavior + 0x424),
    ((u8 *)update_ability_actor_behavior + 0x424),
    ((u8 *)update_ability_actor_behavior + 0x3E8)
};
