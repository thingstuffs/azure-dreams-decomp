#include "common.h"

extern void update_creature_behavior_and_animation(void);

/* jump_table; owner: dungeon/func_80ADDF28. */
const void *const saber_slot_c_behavior_targets[12] __attribute__((aligned(4))) = {
    ((u8 *)update_creature_behavior_and_animation + 0x42C),
    ((u8 *)update_creature_behavior_and_animation + 0x42C),
    ((u8 *)update_creature_behavior_and_animation + 0x42C),
    ((u8 *)update_creature_behavior_and_animation + 0x458),
    ((u8 *)update_creature_behavior_and_animation + 0x3D8),
    ((u8 *)update_creature_behavior_and_animation + 0x3D8),
    ((u8 *)update_creature_behavior_and_animation + 0x3D8),
    ((u8 *)update_creature_behavior_and_animation + 0x384),
    ((u8 *)update_creature_behavior_and_animation + 0x3BC),
    ((u8 *)update_creature_behavior_and_animation + 0x458),
    ((u8 *)update_creature_behavior_and_animation + 0x458),
    ((u8 *)update_creature_behavior_and_animation + 0x41C)
};
