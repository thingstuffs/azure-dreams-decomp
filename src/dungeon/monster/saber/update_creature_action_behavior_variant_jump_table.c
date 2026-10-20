#include "common.h"

extern void update_creature_action_behavior_variant(void);

/* jump_table; owner: dungeon/func_80AE9F28. */
const u32 D_8014C808[12] __attribute__((aligned(4))) = {
    (u32)((u8 *)update_creature_action_behavior_variant + 0x42C),
    (u32)((u8 *)update_creature_action_behavior_variant + 0x42C),
    (u32)((u8 *)update_creature_action_behavior_variant + 0x42C),
    (u32)((u8 *)update_creature_action_behavior_variant + 0x458),
    (u32)((u8 *)update_creature_action_behavior_variant + 0x3D8),
    (u32)((u8 *)update_creature_action_behavior_variant + 0x3D8),
    (u32)((u8 *)update_creature_action_behavior_variant + 0x3D8),
    (u32)((u8 *)update_creature_action_behavior_variant + 0x384),
    (u32)((u8 *)update_creature_action_behavior_variant + 0x3BC),
    (u32)((u8 *)update_creature_action_behavior_variant + 0x458),
    (u32)((u8 *)update_creature_action_behavior_variant + 0x458),
    (u32)((u8 *)update_creature_action_behavior_variant + 0x41C)
};
