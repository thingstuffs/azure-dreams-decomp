#include "common.h"

extern void dungeonUpdateMovingActorLanding(void);

/* jump_table; owner: dungeon/func_80F03000. */
const u32 D_8014C828[5] __attribute__((aligned(4))) = {
    (u32)((u8 *)dungeonUpdateMovingActorLanding + 0x12C),
    (u32)((u8 *)dungeonUpdateMovingActorLanding + 0x134),
    (u32)((u8 *)dungeonUpdateMovingActorLanding + 0x13C),
    (u32)((u8 *)dungeonUpdateMovingActorLanding + 0x144),
    (u32)((u8 *)dungeonUpdateMovingActorLanding + 0x14C)
};
