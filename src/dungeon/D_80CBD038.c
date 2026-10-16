#include "common.h"

extern void dungeonAdvanceSelectedItemAction(void);

/* jump_table; owner: dungeon/func_80CBEF98. */
const u32 D_80170838[7] __attribute__((aligned(4))) = {
    (u32)((u8 *)dungeonAdvanceSelectedItemAction + 0x11C),
    (u32)((u8 *)dungeonAdvanceSelectedItemAction + 0x114),
    (u32)((u8 *)dungeonAdvanceSelectedItemAction + 0x10C),
    (u32)((u8 *)dungeonAdvanceSelectedItemAction + 0x124),
    (u32)((u8 *)dungeonAdvanceSelectedItemAction + 0xCC),
    (u32)((u8 *)dungeonAdvanceSelectedItemAction + 0xC4),
    (u32)((u8 *)dungeonAdvanceSelectedItemAction + 0xBC)
};
