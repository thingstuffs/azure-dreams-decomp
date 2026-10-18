#include "common.h"

extern void dispatch_dungeon_actor_behavior_and_facing(void);

/* jump_table; owner: dungeon/func_80DB3668. */
const u32 D_8014C808[12] __attribute__((aligned(4))) = {
    (u32)((u8 *)dispatch_dungeon_actor_behavior_and_facing + 0x3A0),
    (u32)((u8 *)dispatch_dungeon_actor_behavior_and_facing + 0x3A0),
    (u32)((u8 *)dispatch_dungeon_actor_behavior_and_facing + 0x3A0),
    (u32)((u8 *)dispatch_dungeon_actor_behavior_and_facing + 0x3CC),
    (u32)((u8 *)dispatch_dungeon_actor_behavior_and_facing + 0x34C),
    (u32)((u8 *)dispatch_dungeon_actor_behavior_and_facing + 0x34C),
    (u32)((u8 *)dispatch_dungeon_actor_behavior_and_facing + 0x34C),
    (u32)((u8 *)dispatch_dungeon_actor_behavior_and_facing + 0x2DC),
    (u32)((u8 *)dispatch_dungeon_actor_behavior_and_facing + 0x2CC),
    (u32)((u8 *)dispatch_dungeon_actor_behavior_and_facing + 0x3CC),
    (u32)((u8 *)dispatch_dungeon_actor_behavior_and_facing + 0x3CC),
    (u32)((u8 *)dispatch_dungeon_actor_behavior_and_facing + 0x390)
};
