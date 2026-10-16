#include "common.h"

extern void advanceActorAbilityAction(void);

/* jump_table; owner: dungeon/func_80FC55EC. */
const u32 D_8015E850[7] __attribute__((aligned(4))) = {
    (u32)((u8 *)advanceActorAbilityAction + 0x11C),
    (u32)((u8 *)advanceActorAbilityAction + 0x114),
    (u32)((u8 *)advanceActorAbilityAction + 0x10C),
    (u32)((u8 *)advanceActorAbilityAction + 0x124),
    (u32)((u8 *)advanceActorAbilityAction + 0xCC),
    (u32)((u8 *)advanceActorAbilityAction + 0xC4),
    (u32)((u8 *)advanceActorAbilityAction + 0xBC)
};
