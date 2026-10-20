#include "common.h"

extern void update_creature_actions_and_animation(void);

/* jump_table; owner: dungeon/func_80CC0398. */
const u32 D_80170858[12] __attribute__((aligned(4))) = {
    (u32)((u8 *)update_creature_actions_and_animation + 0x360),
    (u32)((u8 *)update_creature_actions_and_animation + 0x360),
    (u32)((u8 *)update_creature_actions_and_animation + 0x360),
    (u32)((u8 *)update_creature_actions_and_animation + 0x370),
    (u32)((u8 *)update_creature_actions_and_animation + 0x360),
    (u32)((u8 *)update_creature_actions_and_animation + 0x360),
    (u32)((u8 *)update_creature_actions_and_animation + 0x360),
    (u32)((u8 *)update_creature_actions_and_animation + 0x360),
    (u32)((u8 *)update_creature_actions_and_animation + 0x33C),
    (u32)((u8 *)update_creature_actions_and_animation + 0x370),
    (u32)((u8 *)update_creature_actions_and_animation + 0x370),
    (u32)((u8 *)update_creature_actions_and_animation + 0x360)
};
