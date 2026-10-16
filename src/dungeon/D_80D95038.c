#include "common.h"

extern void dungeonAdvanceActorAbility(void);

/* jump_table; owner: dungeon/func_80D97070. */
const u32 D_8016A838[7] __attribute__((aligned(4))) = {
    (u32)((u8 *)dungeonAdvanceActorAbility + 0x11C),
    (u32)((u8 *)dungeonAdvanceActorAbility + 0x114),
    (u32)((u8 *)dungeonAdvanceActorAbility + 0x10C),
    (u32)((u8 *)dungeonAdvanceActorAbility + 0x124),
    (u32)((u8 *)dungeonAdvanceActorAbility + 0xCC),
    (u32)((u8 *)dungeonAdvanceActorAbility + 0xC4),
    (u32)((u8 *)dungeonAdvanceActorAbility + 0xBC)
};
