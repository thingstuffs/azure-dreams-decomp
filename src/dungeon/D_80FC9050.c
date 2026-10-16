#include "common.h"

extern void dungeonUpdateItemSlotAction(void);

/* jump_table; owner: dungeon/func_80FCB5EC. */
const u32 D_80158850[7] __attribute__((aligned(4))) = {
    (u32)((u8 *)dungeonUpdateItemSlotAction + 0x11C),
    (u32)((u8 *)dungeonUpdateItemSlotAction + 0x114),
    (u32)((u8 *)dungeonUpdateItemSlotAction + 0x10C),
    (u32)((u8 *)dungeonUpdateItemSlotAction + 0x124),
    (u32)((u8 *)dungeonUpdateItemSlotAction + 0xCC),
    (u32)((u8 *)dungeonUpdateItemSlotAction + 0xC4),
    (u32)((u8 *)dungeonUpdateItemSlotAction + 0xBC)
};
