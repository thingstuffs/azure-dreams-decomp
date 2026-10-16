#include "common.h"

extern void dungeonAdvanceItemVisualAction(void);

/* Exact jump_table span; dispatch consumer dungeon/func_80DBBFC8. */
const u32 D_80170838[7] __attribute__((aligned(4))) = {
    (u32)((u8 *)dungeonAdvanceItemVisualAction + 0x130),
    (u32)((u8 *)dungeonAdvanceItemVisualAction + 0x128),
    (u32)((u8 *)dungeonAdvanceItemVisualAction + 0x120),
    (u32)((u8 *)dungeonAdvanceItemVisualAction + 0x138),
    (u32)((u8 *)dungeonAdvanceItemVisualAction + 0xE0),
    (u32)((u8 *)dungeonAdvanceItemVisualAction + 0xD8),
    (u32)((u8 *)dungeonAdvanceItemVisualAction + 0xD0)
};
