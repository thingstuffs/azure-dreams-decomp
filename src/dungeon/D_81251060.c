#include "common.h"

extern void dungeonAdvanceActorActionAndTarget(void);

/* jump_table; owner: dungeon/func_81252D6C. */
const u32 D_80170860[7] __attribute__((aligned(4))) = {
    (u32)((u8 *)dungeonAdvanceActorActionAndTarget + 0x114),
    (u32)((u8 *)dungeonAdvanceActorActionAndTarget + 0x10C),
    (u32)((u8 *)dungeonAdvanceActorActionAndTarget + 0x104),
    (u32)((u8 *)dungeonAdvanceActorActionAndTarget + 0x11C),
    (u32)((u8 *)dungeonAdvanceActorActionAndTarget + 0xC0),
    (u32)((u8 *)dungeonAdvanceActorActionAndTarget + 0xB8),
    (u32)((u8 *)dungeonAdvanceActorActionAndTarget + 0xB0)
};
