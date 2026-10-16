#include "common.h"

extern void dungeonUpdateOverlayItemUse(void);

/* jump_table; owner: dungeon/func_80FE91A0. */
const u32 D_80164838[7] __attribute__((aligned(4))) = {
    (u32)((u8 *)dungeonUpdateOverlayItemUse + 0x124),
    (u32)((u8 *)dungeonUpdateOverlayItemUse + 0x11C),
    (u32)((u8 *)dungeonUpdateOverlayItemUse + 0x114),
    (u32)((u8 *)dungeonUpdateOverlayItemUse + 0x12C),
    (u32)((u8 *)dungeonUpdateOverlayItemUse + 0xD4),
    (u32)((u8 *)dungeonUpdateOverlayItemUse + 0xCC),
    (u32)((u8 *)dungeonUpdateOverlayItemUse + 0xC4)
};
