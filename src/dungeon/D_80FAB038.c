#include "common.h"

extern void dungeonUpdateActorItemTargetAction(void);

/* jump_table; owner: dungeon/func_80FAD240. */
const u32 D_8014C838[7] __attribute__((aligned(4))) = {
    (u32)((u8 *)dungeonUpdateActorItemTargetAction + 0x11C),
    (u32)((u8 *)dungeonUpdateActorItemTargetAction + 0x114),
    (u32)((u8 *)dungeonUpdateActorItemTargetAction + 0x10C),
    (u32)((u8 *)dungeonUpdateActorItemTargetAction + 0x124),
    (u32)((u8 *)dungeonUpdateActorItemTargetAction + 0xCC),
    (u32)((u8 *)dungeonUpdateActorItemTargetAction + 0xC4),
    (u32)((u8 *)dungeonUpdateActorItemTargetAction + 0xBC)
};
