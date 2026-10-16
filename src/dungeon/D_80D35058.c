#include "common.h"

extern void dungeonUpdateActorAbilityAction(void);

/* jump_table; owner: dungeon/func_80D37E4C. */
const u32 D_8014C858[7] __attribute__((aligned(4))) = {
    (u32)((u8 *)dungeonUpdateActorAbilityAction + 0x120),
    (u32)((u8 *)dungeonUpdateActorAbilityAction + 0x118),
    (u32)((u8 *)dungeonUpdateActorAbilityAction + 0x110),
    (u32)((u8 *)dungeonUpdateActorAbilityAction + 0x128),
    (u32)((u8 *)dungeonUpdateActorAbilityAction + 0xD0),
    (u32)((u8 *)dungeonUpdateActorAbilityAction + 0xC8),
    (u32)((u8 *)dungeonUpdateActorAbilityAction + 0xC0)
};
