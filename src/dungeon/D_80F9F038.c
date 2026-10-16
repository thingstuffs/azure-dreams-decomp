#include "common.h"

extern void dungeonAdvanceItemActionVariantB(void);

/* jump_table; owner: dungeon/func_80FA1240. */
const u32 D_80158838[7] __attribute__((aligned(4))) = {
    (u32)((u8 *)dungeonAdvanceItemActionVariantB + 0x11C),
    (u32)((u8 *)dungeonAdvanceItemActionVariantB + 0x114),
    (u32)((u8 *)dungeonAdvanceItemActionVariantB + 0x10C),
    (u32)((u8 *)dungeonAdvanceItemActionVariantB + 0x124),
    (u32)((u8 *)dungeonAdvanceItemActionVariantB + 0xCC),
    (u32)((u8 *)dungeonAdvanceItemActionVariantB + 0xC4),
    (u32)((u8 *)dungeonAdvanceItemActionVariantB + 0xBC)
};
