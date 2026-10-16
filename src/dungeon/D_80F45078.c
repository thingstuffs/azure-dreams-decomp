#include "common.h"

extern void dungeonUpdateEffectActionVariant(void);

/* jump_table; owner: dungeon/func_80F4775C. */
const u32 D_8015E878[7] __attribute__((aligned(4))) = {
    (u32)((u8 *)dungeonUpdateEffectActionVariant + 0x11C),
    (u32)((u8 *)dungeonUpdateEffectActionVariant + 0x114),
    (u32)((u8 *)dungeonUpdateEffectActionVariant + 0x10C),
    (u32)((u8 *)dungeonUpdateEffectActionVariant + 0x124),
    (u32)((u8 *)dungeonUpdateEffectActionVariant + 0xCC),
    (u32)((u8 *)dungeonUpdateEffectActionVariant + 0xC4),
    (u32)((u8 *)dungeonUpdateEffectActionVariant + 0xBC)
};
