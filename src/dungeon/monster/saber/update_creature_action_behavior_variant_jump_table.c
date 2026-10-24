#include "common.h"

extern void update_creature_action_behavior_variant(void);

/* jump_table; owner: dungeon/func_80AE9F28. */
const void *const saber_slot_a_behavior_targets[12] __attribute__((aligned(4))) = {
    ((u8 *)update_creature_action_behavior_variant + 0x42C),
    ((u8 *)update_creature_action_behavior_variant + 0x42C),
    ((u8 *)update_creature_action_behavior_variant + 0x42C),
    ((u8 *)update_creature_action_behavior_variant + 0x458),
    ((u8 *)update_creature_action_behavior_variant + 0x3D8),
    ((u8 *)update_creature_action_behavior_variant + 0x3D8),
    ((u8 *)update_creature_action_behavior_variant + 0x3D8),
    ((u8 *)update_creature_action_behavior_variant + 0x384),
    ((u8 *)update_creature_action_behavior_variant + 0x3BC),
    ((u8 *)update_creature_action_behavior_variant + 0x458),
    ((u8 *)update_creature_action_behavior_variant + 0x458),
    ((u8 *)update_creature_action_behavior_variant + 0x41C)
};
