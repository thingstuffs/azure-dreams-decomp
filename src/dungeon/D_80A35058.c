#include "common.h"

extern void dungeonUpdateActorBehaviorFourth(void);

/* jump_table; owner: dungeon/func_80A370C4. */
const u32 D_80158858[7] __attribute__((aligned(4))) = {
    (u32)((u8 *)dungeonUpdateActorBehaviorFourth + 0x128),
    (u32)((u8 *)dungeonUpdateActorBehaviorFourth + 0x120),
    (u32)((u8 *)dungeonUpdateActorBehaviorFourth + 0x118),
    (u32)((u8 *)dungeonUpdateActorBehaviorFourth + 0x130),
    (u32)((u8 *)dungeonUpdateActorBehaviorFourth + 0xD8),
    (u32)((u8 *)dungeonUpdateActorBehaviorFourth + 0xD0),
    (u32)((u8 *)dungeonUpdateActorBehaviorFourth + 0xC8)
};
