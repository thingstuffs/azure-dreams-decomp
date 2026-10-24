#include "common.h"

extern void reset_actor_action_after_ability(void);

/* jump_table; owner: dungeon/func_80D23F60. */
const void *const noise_slot_d_behavior_targets[12] __attribute__((aligned(4))) = {
    ((u8 *)reset_actor_action_after_ability + 0x3F8),
    ((u8 *)reset_actor_action_after_ability + 0x3F8),
    ((u8 *)reset_actor_action_after_ability + 0x3F8),
    ((u8 *)reset_actor_action_after_ability + 0x424),
    ((u8 *)reset_actor_action_after_ability + 0x3A4),
    ((u8 *)reset_actor_action_after_ability + 0x3A4),
    ((u8 *)reset_actor_action_after_ability + 0x3A4),
    ((u8 *)reset_actor_action_after_ability + 0x350),
    ((u8 *)reset_actor_action_after_ability + 0x388),
    ((u8 *)reset_actor_action_after_ability + 0x424),
    ((u8 *)reset_actor_action_after_ability + 0x424),
    ((u8 *)reset_actor_action_after_ability + 0x3E8)
};
