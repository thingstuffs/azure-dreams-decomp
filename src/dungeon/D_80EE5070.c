#include "common.h"

extern void dungeonAdvanceFlashingSpriteSequence(void);

/* jump_table; owner: dungeon/func_80EE7D14. */
const u32 D_8016A870[5] __attribute__((aligned(4))) = {
    (u32)((u8 *)dungeonAdvanceFlashingSpriteSequence + 0x48),
    (u32)((u8 *)dungeonAdvanceFlashingSpriteSequence + 0xD4),
    (u32)((u8 *)dungeonAdvanceFlashingSpriteSequence + 0x118),
    (u32)((u8 *)dungeonAdvanceFlashingSpriteSequence + 0x178),
    (u32)((u8 *)dungeonAdvanceFlashingSpriteSequence + 0x23C)
};
