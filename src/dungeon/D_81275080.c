#include "common.h"

extern void dungeonAdvanceFacingEffectSequence(void);

/* jump_table; owner: dungeon/func_812776C4. */
const u32 D_8014C880[6] __attribute__((aligned(4))) = {
    (u32)((u8 *)dungeonAdvanceFacingEffectSequence + 0x5C),
    (u32)((u8 *)dungeonAdvanceFacingEffectSequence + 0xCC),
    (u32)((u8 *)dungeonAdvanceFacingEffectSequence + 0xE4),
    (u32)((u8 *)dungeonAdvanceFacingEffectSequence + 0x110),
    (u32)((u8 *)dungeonAdvanceFacingEffectSequence + 0x38C),
    (u32)((u8 *)dungeonAdvanceFacingEffectSequence + 0x3FC)
};
