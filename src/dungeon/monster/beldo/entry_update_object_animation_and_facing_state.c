#include "common.h"

extern void update_object_animation_and_facing_state(void);

/* jump_table; owner: dungeon/func_81257D14. */
const void *const beldo_slot_f_behavior_targets[12] __attribute__((aligned(4))) = {
    ((u8 *)update_object_animation_and_facing_state + 0x3AC),
    ((u8 *)update_object_animation_and_facing_state + 0x3AC),
    ((u8 *)update_object_animation_and_facing_state + 0x3AC),
    ((u8 *)update_object_animation_and_facing_state + 0x3D4),
    ((u8 *)update_object_animation_and_facing_state + 0x380),
    ((u8 *)update_object_animation_and_facing_state + 0x380),
    ((u8 *)update_object_animation_and_facing_state + 0x380),
    ((u8 *)update_object_animation_and_facing_state + 0x380),
    ((u8 *)update_object_animation_and_facing_state + 0x380),
    ((u8 *)update_object_animation_and_facing_state + 0x3D4),
    ((u8 *)update_object_animation_and_facing_state + 0x3D4),
    ((u8 *)update_object_animation_and_facing_state + 0x370)
};
