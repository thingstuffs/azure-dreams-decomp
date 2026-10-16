#include "common.h"

extern void updateActorAbilityActionAndEffects(void);

/* jump_table; owner: dungeon/func_80FA7240. */
const u32 D_80152838[7] __attribute__((aligned(4))) = {
    (u32)((u8 *)updateActorAbilityActionAndEffects + 0x11C),
    (u32)((u8 *)updateActorAbilityActionAndEffects + 0x114),
    (u32)((u8 *)updateActorAbilityActionAndEffects + 0x10C),
    (u32)((u8 *)updateActorAbilityActionAndEffects + 0x124),
    (u32)((u8 *)updateActorAbilityActionAndEffects + 0xCC),
    (u32)((u8 *)updateActorAbilityActionAndEffects + 0xC4),
    (u32)((u8 *)updateActorAbilityActionAndEffects + 0xBC)
};
