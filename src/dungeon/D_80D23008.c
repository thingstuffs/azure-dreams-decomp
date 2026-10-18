#include "common.h"

extern void reset_actor_action_after_ability(void);

/* jump_table; owner: dungeon/func_80D23F60. */
const u32 D_8015E808[12] __attribute__((aligned(4))) = {
    (u32)((u8 *)reset_actor_action_after_ability + 0x3F8),
    (u32)((u8 *)reset_actor_action_after_ability + 0x3F8),
    (u32)((u8 *)reset_actor_action_after_ability + 0x3F8),
    (u32)((u8 *)reset_actor_action_after_ability + 0x424),
    (u32)((u8 *)reset_actor_action_after_ability + 0x3A4),
    (u32)((u8 *)reset_actor_action_after_ability + 0x3A4),
    (u32)((u8 *)reset_actor_action_after_ability + 0x3A4),
    (u32)((u8 *)reset_actor_action_after_ability + 0x350),
    (u32)((u8 *)reset_actor_action_after_ability + 0x388),
    (u32)((u8 *)reset_actor_action_after_ability + 0x424),
    (u32)((u8 *)reset_actor_action_after_ability + 0x424),
    (u32)((u8 *)reset_actor_action_after_ability + 0x3E8)
};
