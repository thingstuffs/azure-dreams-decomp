#include "common.h"

extern void update_effect_actor_behavior(void);

/* jump_table; owner: dungeon/func_80EE04E8. */
const u32 D_80170840[12] __attribute__((aligned(4))) = {
    (u32)((u8 *)update_effect_actor_behavior + 0x3E4),
    (u32)((u8 *)update_effect_actor_behavior + 0x3E4),
    (u32)((u8 *)update_effect_actor_behavior + 0x3E4),
    (u32)((u8 *)update_effect_actor_behavior + 0x410),
    (u32)((u8 *)update_effect_actor_behavior + 0x390),
    (u32)((u8 *)update_effect_actor_behavior + 0x390),
    (u32)((u8 *)update_effect_actor_behavior + 0x390),
    (u32)((u8 *)update_effect_actor_behavior + 0x33C),
    (u32)((u8 *)update_effect_actor_behavior + 0x374),
    (u32)((u8 *)update_effect_actor_behavior + 0x410),
    (u32)((u8 *)update_effect_actor_behavior + 0x410),
    (u32)((u8 *)update_effect_actor_behavior + 0x3D4)
};
