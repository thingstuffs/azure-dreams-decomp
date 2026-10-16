#include "common.h"

extern void dungeonAdvanceActorActionPhase(void);

/* jump_table; owner: dungeon/func_81276D6C. */
const u32 D_8014C838[9] __attribute__((aligned(4))) = {
    (u32)((u8 *)dungeonAdvanceActorActionPhase + 0x64),
    (u32)((u8 *)dungeonAdvanceActorActionPhase + 0x2A8),
    (u32)((u8 *)dungeonAdvanceActorActionPhase + 0x2F0),
    (u32)((u8 *)dungeonAdvanceActorActionPhase + 0x330),
    (u32)((u8 *)dungeonAdvanceActorActionPhase + 0x3D0),
    (u32)((u8 *)dungeonAdvanceActorActionPhase + 0x43C),
    (u32)((u8 *)dungeonAdvanceActorActionPhase + 0x4A4),
    (u32)((u8 *)dungeonAdvanceActorActionPhase + 0x4C4),
    (u32)((u8 *)dungeonAdvanceActorActionPhase + 0x558)
};
