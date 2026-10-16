#include "common.h"

extern void dungeonUpdatePairedActorMovementAndTiles(void);

/* jump_table; owner: dungeon/func_8102C664. */
const u32 D_8014C878[5] __attribute__((aligned(4))) = {
    (u32)((u8 *)dungeonUpdatePairedActorMovementAndTiles + 0x7C),
    (u32)((u8 *)dungeonUpdatePairedActorMovementAndTiles + 0x294),
    (u32)((u8 *)dungeonUpdatePairedActorMovementAndTiles + 0x3A0),
    (u32)((u8 *)dungeonUpdatePairedActorMovementAndTiles + 0x694),
    (u32)((u8 *)dungeonUpdatePairedActorMovementAndTiles + 0x804)
};
