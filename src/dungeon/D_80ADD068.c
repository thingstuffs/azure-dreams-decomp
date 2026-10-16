#include "common.h"

extern void advanceActorAbilityAndCompletion(void);

/* jump_table; owner: dungeon/func_80ADFA30. */
const u32 D_80158868[7] __attribute__((aligned(4))) = {
    (u32)((u8 *)advanceActorAbilityAndCompletion + 0x11C),
    (u32)((u8 *)advanceActorAbilityAndCompletion + 0x114),
    (u32)((u8 *)advanceActorAbilityAndCompletion + 0x10C),
    (u32)((u8 *)advanceActorAbilityAndCompletion + 0x124),
    (u32)((u8 *)advanceActorAbilityAndCompletion + 0xC8),
    (u32)((u8 *)advanceActorAbilityAndCompletion + 0xC0),
    (u32)((u8 *)advanceActorAbilityAndCompletion + 0xB8)
};
