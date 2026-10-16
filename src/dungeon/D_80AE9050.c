#include "common.h"

extern void dungeonAdvanceMultiSlotActionSequence(void);

/* jump_table; owner: dungeon/func_80AEBA30. */
const u32 D_8014C850[5] __attribute__((aligned(4))) = {
    (u32)((u8 *)dungeonAdvanceMultiSlotActionSequence + 0x6C),
    (u32)((u8 *)dungeonAdvanceMultiSlotActionSequence + 0x29C),
    (u32)((u8 *)dungeonAdvanceMultiSlotActionSequence + 0x2E4),
    (u32)((u8 *)dungeonAdvanceMultiSlotActionSequence + 0x514),
    (u32)((u8 *)dungeonAdvanceMultiSlotActionSequence + 0x59C)
};
