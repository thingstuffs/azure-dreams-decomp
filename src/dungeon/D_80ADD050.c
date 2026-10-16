#include "common.h"

extern void advanceActorAbilityAndCompletion(void);

/* jump_table; owner: dungeon/func_80ADFA30. */
const u32 D_80158850[5] __attribute__((aligned(4))) = {
    (u32)((u8 *)advanceActorAbilityAndCompletion + 0x6C),
    (u32)((u8 *)advanceActorAbilityAndCompletion + 0x29C),
    (u32)((u8 *)advanceActorAbilityAndCompletion + 0x2E4),
    (u32)((u8 *)advanceActorAbilityAndCompletion + 0x514),
    (u32)((u8 *)advanceActorAbilityAndCompletion + 0x59C)
};
