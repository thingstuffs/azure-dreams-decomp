#include "common.h"

extern void update_creature_action_and_animation(void);

/* jump_table; owner: dungeon/func_80FD576C. */
const u32 mandara_slot_a_behavior_targets[5] __attribute__((aligned(4))) = {
    (u32)((u8 *)update_creature_action_and_animation + 0x1C0),
    (u32)((u8 *)update_creature_action_and_animation + 0x22C),
    (u32)((u8 *)update_creature_action_and_animation + 0x300),
    (u32)((u8 *)update_creature_action_and_animation + 0x490),
    (u32)((u8 *)update_creature_action_and_animation + 0x4D8)
};
