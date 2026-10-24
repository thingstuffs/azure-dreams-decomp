#include "common.h"

extern void update_creature_action_and_animation(void);

/* jump_table; owner: dungeon/func_80FD576C. */
const void *const mandara_slot_a_behavior_targets[5] __attribute__((aligned(4))) = {
    ((u8 *)update_creature_action_and_animation + 0x1C0),
    ((u8 *)update_creature_action_and_animation + 0x22C),
    ((u8 *)update_creature_action_and_animation + 0x300),
    ((u8 *)update_creature_action_and_animation + 0x490),
    ((u8 *)update_creature_action_and_animation + 0x4D8)
};
