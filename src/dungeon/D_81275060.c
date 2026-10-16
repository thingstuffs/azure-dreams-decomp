#include "common.h"

extern void dungeonAdvanceActorActionPhase(void);

/* jump_table; owner: dungeon/func_81276D6C. */
const u32 D_8014C860[7] __attribute__((aligned(4))) = {
    (u32)((u8 *)dungeonAdvanceActorActionPhase + 0x114),
    (u32)((u8 *)dungeonAdvanceActorActionPhase + 0x10C),
    (u32)((u8 *)dungeonAdvanceActorActionPhase + 0x104),
    (u32)((u8 *)dungeonAdvanceActorActionPhase + 0x11C),
    (u32)((u8 *)dungeonAdvanceActorActionPhase + 0xC0),
    (u32)((u8 *)dungeonAdvanceActorActionPhase + 0xB8),
    (u32)((u8 *)dungeonAdvanceActorActionPhase + 0xB0)
};
