#include "common.h"

extern void update_creature_action_and_animation(void);

/* jump_table; owner: dungeon/func_80FD576C. */
const u32 D_8014C820[12] __attribute__((aligned(4))) = {
    (u32)((u8 *)update_creature_action_and_animation + 0x828),
    (u32)((u8 *)update_creature_action_and_animation + 0x828),
    (u32)((u8 *)update_creature_action_and_animation + 0x828),
    (u32)((u8 *)update_creature_action_and_animation + 0x854),
    (u32)((u8 *)update_creature_action_and_animation + 0x7D4),
    (u32)((u8 *)update_creature_action_and_animation + 0x7D4),
    (u32)((u8 *)update_creature_action_and_animation + 0x7D4),
    (u32)((u8 *)update_creature_action_and_animation + 0x76C),
    (u32)((u8 *)update_creature_action_and_animation + 0x76C),
    (u32)((u8 *)update_creature_action_and_animation + 0x854),
    (u32)((u8 *)update_creature_action_and_animation + 0x854),
    (u32)((u8 *)update_creature_action_and_animation + 0x818)
};
