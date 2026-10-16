#include "common.h"

extern void dungeonStartActorActionAndReset(void);

/* jump_table; owner: dungeon/func_8102B034. */
const u32 D_8014C858[7] __attribute__((aligned(4))) = {
    (u32)((u8 *)dungeonStartActorActionAndReset + 0x11C),
    (u32)((u8 *)dungeonStartActorActionAndReset + 0x114),
    (u32)((u8 *)dungeonStartActorActionAndReset + 0x10C),
    (u32)((u8 *)dungeonStartActorActionAndReset + 0x124),
    (u32)((u8 *)dungeonStartActorActionAndReset + 0xCC),
    (u32)((u8 *)dungeonStartActorActionAndReset + 0xC4),
    (u32)((u8 *)dungeonStartActorActionAndReset + 0xBC)
};
