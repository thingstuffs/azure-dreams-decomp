#include "common.h"

extern void advanceAbilityActionAndResetState(void);

/* jump_table; owner: dungeon/func_80D25E4C. */
const u32 D_8015E858[7] __attribute__((aligned(4))) = {
    (u32)((u8 *)advanceAbilityActionAndResetState + 0x120),
    (u32)((u8 *)advanceAbilityActionAndResetState + 0x118),
    (u32)((u8 *)advanceAbilityActionAndResetState + 0x110),
    (u32)((u8 *)advanceAbilityActionAndResetState + 0x128),
    (u32)((u8 *)advanceAbilityActionAndResetState + 0xD0),
    (u32)((u8 *)advanceAbilityActionAndResetState + 0xC8),
    (u32)((u8 *)advanceAbilityActionAndResetState + 0xC0)
};
