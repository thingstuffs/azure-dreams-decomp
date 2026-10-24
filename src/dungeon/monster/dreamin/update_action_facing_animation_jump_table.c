#include "common.h"

extern void update_action_facing_animation(void);

/* jump_table; owner: dungeon/func_80D95668. */
const void *const dreamin_slot_f_behavior_targets[12] __attribute__((aligned(4))) = {
    ((u8 *)update_action_facing_animation + 0x3A0),
    ((u8 *)update_action_facing_animation + 0x3A0),
    ((u8 *)update_action_facing_animation + 0x3A0),
    ((u8 *)update_action_facing_animation + 0x3CC),
    ((u8 *)update_action_facing_animation + 0x34C),
    ((u8 *)update_action_facing_animation + 0x34C),
    ((u8 *)update_action_facing_animation + 0x34C),
    ((u8 *)update_action_facing_animation + 0x2DC),
    ((u8 *)update_action_facing_animation + 0x2CC),
    ((u8 *)update_action_facing_animation + 0x3CC),
    ((u8 *)update_action_facing_animation + 0x3CC),
    ((u8 *)update_action_facing_animation + 0x390)
};
