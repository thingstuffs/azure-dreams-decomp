#include "common.h"

extern void advanceActorAnimationAndResetMotion(void);

/* jump_table; owner: dungeon/func_8106D1D4. */
const u32 D_8015E838[7] __attribute__((aligned(4))) = {
    (u32)((u8 *)advanceActorAnimationAndResetMotion + 0x11C),
    (u32)((u8 *)advanceActorAnimationAndResetMotion + 0x114),
    (u32)((u8 *)advanceActorAnimationAndResetMotion + 0x10C),
    (u32)((u8 *)advanceActorAnimationAndResetMotion + 0x124),
    (u32)((u8 *)advanceActorAnimationAndResetMotion + 0xCC),
    (u32)((u8 *)advanceActorAnimationAndResetMotion + 0xC4),
    (u32)((u8 *)advanceActorAnimationAndResetMotion + 0xBC)
};
