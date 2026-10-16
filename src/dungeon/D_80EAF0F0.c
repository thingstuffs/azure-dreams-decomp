#include "common.h"

extern void dungeonUpdateActorMovementRecovery(void);

/* jump_table; owner: dungeon/func_80EB2C28. */
const u32 D_8014C8F0[6] __attribute__((aligned(4))) = {
    (u32)((u8 *)dungeonUpdateActorMovementRecovery + 0x90),
    (u32)((u8 *)dungeonUpdateActorMovementRecovery + 0x130),
    (u32)((u8 *)dungeonUpdateActorMovementRecovery + 0x1C0),
    (u32)((u8 *)dungeonUpdateActorMovementRecovery + 0x24C),
    (u32)((u8 *)dungeonUpdateActorMovementRecovery + 0x2BC),
    (u32)((u8 *)dungeonUpdateActorMovementRecovery + 0x39C)
};
