#include "common.h"

extern void dungeonAdvanceActorAnimationAndResetMovement(void);

/* jump_table; owner: dungeon/func_8107F1D4. */
const u32 D_8014C838[7] __attribute__((aligned(4))) = {
    (u32)((u8 *)dungeonAdvanceActorAnimationAndResetMovement + 0x11C),
    (u32)((u8 *)dungeonAdvanceActorAnimationAndResetMovement + 0x114),
    (u32)((u8 *)dungeonAdvanceActorAnimationAndResetMovement + 0x10C),
    (u32)((u8 *)dungeonAdvanceActorAnimationAndResetMovement + 0x124),
    (u32)((u8 *)dungeonAdvanceActorAnimationAndResetMovement + 0xCC),
    (u32)((u8 *)dungeonAdvanceActorAnimationAndResetMovement + 0xC4),
    (u32)((u8 *)dungeonAdvanceActorAnimationAndResetMovement + 0xBC)
};
