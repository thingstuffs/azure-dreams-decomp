#include "common.h"

extern void update_actor_behavior_and_idle_delay(void);

/* jump_table; owner: dungeon/func_80D17F60. */
const u32 noise_slot_f_behavior_targets[12] __attribute__((aligned(4))) = {
    (u32)((u8 *)update_actor_behavior_and_idle_delay + 0x3F8),
    (u32)((u8 *)update_actor_behavior_and_idle_delay + 0x3F8),
    (u32)((u8 *)update_actor_behavior_and_idle_delay + 0x3F8),
    (u32)((u8 *)update_actor_behavior_and_idle_delay + 0x424),
    (u32)((u8 *)update_actor_behavior_and_idle_delay + 0x3A4),
    (u32)((u8 *)update_actor_behavior_and_idle_delay + 0x3A4),
    (u32)((u8 *)update_actor_behavior_and_idle_delay + 0x3A4),
    (u32)((u8 *)update_actor_behavior_and_idle_delay + 0x350),
    (u32)((u8 *)update_actor_behavior_and_idle_delay + 0x388),
    (u32)((u8 *)update_actor_behavior_and_idle_delay + 0x424),
    (u32)((u8 *)update_actor_behavior_and_idle_delay + 0x424),
    (u32)((u8 *)update_actor_behavior_and_idle_delay + 0x3E8)
};
