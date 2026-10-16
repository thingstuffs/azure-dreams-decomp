#include "common.h"

extern void dungeonUpdateMovementDestinationAndRecovery(void);

/* jump_table; owner: dungeon/func_80E94C28. */
const u32 D_8016A8F0[6] __attribute__((aligned(4))) = {
    (u32)((u8 *)dungeonUpdateMovementDestinationAndRecovery + 0x90),
    (u32)((u8 *)dungeonUpdateMovementDestinationAndRecovery + 0x130),
    (u32)((u8 *)dungeonUpdateMovementDestinationAndRecovery + 0x1C0),
    (u32)((u8 *)dungeonUpdateMovementDestinationAndRecovery + 0x24C),
    (u32)((u8 *)dungeonUpdateMovementDestinationAndRecovery + 0x2BC),
    (u32)((u8 *)dungeonUpdateMovementDestinationAndRecovery + 0x39C)
};
