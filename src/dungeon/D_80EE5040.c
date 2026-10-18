#include "common.h"

extern void update_actor_dungeon_behavior(void);

/* jump_table; owner: dungeon/func_80EE64E8. */
const u32 D_8016A840[12] __attribute__((aligned(4))) = {
    (u32)((u8 *)update_actor_dungeon_behavior + 0x3E4),
    (u32)((u8 *)update_actor_dungeon_behavior + 0x3E4),
    (u32)((u8 *)update_actor_dungeon_behavior + 0x3E4),
    (u32)((u8 *)update_actor_dungeon_behavior + 0x410),
    (u32)((u8 *)update_actor_dungeon_behavior + 0x390),
    (u32)((u8 *)update_actor_dungeon_behavior + 0x390),
    (u32)((u8 *)update_actor_dungeon_behavior + 0x390),
    (u32)((u8 *)update_actor_dungeon_behavior + 0x33C),
    (u32)((u8 *)update_actor_dungeon_behavior + 0x374),
    (u32)((u8 *)update_actor_dungeon_behavior + 0x410),
    (u32)((u8 *)update_actor_dungeon_behavior + 0x410),
    (u32)((u8 *)update_actor_dungeon_behavior + 0x3D4)
};
