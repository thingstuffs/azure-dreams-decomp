#include "common.h"

extern void update_action_facing_animation(void);

/* jump_table; owner: dungeon/func_80D95668. */
const u32 dreamin_slot_f_behavior_targets[12] __attribute__((aligned(4))) = {
    (u32)((u8 *)update_action_facing_animation + 0x3A0),
    (u32)((u8 *)update_action_facing_animation + 0x3A0),
    (u32)((u8 *)update_action_facing_animation + 0x3A0),
    (u32)((u8 *)update_action_facing_animation + 0x3CC),
    (u32)((u8 *)update_action_facing_animation + 0x34C),
    (u32)((u8 *)update_action_facing_animation + 0x34C),
    (u32)((u8 *)update_action_facing_animation + 0x34C),
    (u32)((u8 *)update_action_facing_animation + 0x2DC),
    (u32)((u8 *)update_action_facing_animation + 0x2CC),
    (u32)((u8 *)update_action_facing_animation + 0x3CC),
    (u32)((u8 *)update_action_facing_animation + 0x3CC),
    (u32)((u8 *)update_action_facing_animation + 0x390)
};
