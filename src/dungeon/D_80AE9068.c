#include "common.h"

extern void dungeonAdvanceMultiSlotActionSequence(void);

/* jump_table; owner: dungeon/func_80AEBA30. */
const u32 D_8014C868[7] __attribute__((aligned(4))) = {
    (u32)((u8 *)dungeonAdvanceMultiSlotActionSequence + 0x11C),
    (u32)((u8 *)dungeonAdvanceMultiSlotActionSequence + 0x114),
    (u32)((u8 *)dungeonAdvanceMultiSlotActionSequence + 0x10C),
    (u32)((u8 *)dungeonAdvanceMultiSlotActionSequence + 0x124),
    (u32)((u8 *)dungeonAdvanceMultiSlotActionSequence + 0xC8),
    (u32)((u8 *)dungeonAdvanceMultiSlotActionSequence + 0xC0),
    (u32)((u8 *)dungeonAdvanceMultiSlotActionSequence + 0xB8)
};
