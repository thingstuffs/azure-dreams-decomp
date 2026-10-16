#include "common.h"

extern void dungeonUpdateAbilityActorAction(void);

/* jump_table; owner: dungeon/func_80D2BE4C. */
const u32 D_80158858[7] __attribute__((aligned(4))) = {
    (u32)((u8 *)dungeonUpdateAbilityActorAction + 0x120),
    (u32)((u8 *)dungeonUpdateAbilityActorAction + 0x118),
    (u32)((u8 *)dungeonUpdateAbilityActorAction + 0x110),
    (u32)((u8 *)dungeonUpdateAbilityActorAction + 0x128),
    (u32)((u8 *)dungeonUpdateAbilityActorAction + 0xD0),
    (u32)((u8 *)dungeonUpdateAbilityActorAction + 0xC8),
    (u32)((u8 *)dungeonUpdateAbilityActorAction + 0xC0)
};
