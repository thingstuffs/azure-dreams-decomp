#include "common.h"

extern void dungeonAdvanceSequenceAction(void);

/* jump_table; owner: dungeon/func_80ACD7D8. */
const u32 D_8016A838[5] __attribute__((aligned(4))) = {
    (u32)((u8 *)dungeonAdvanceSequenceAction + 0x48),
    (u32)((u8 *)dungeonAdvanceSequenceAction + 0x98),
    (u32)((u8 *)dungeonAdvanceSequenceAction + 0x10C),
    (u32)((u8 *)dungeonAdvanceSequenceAction + 0x180),
    (u32)((u8 *)dungeonAdvanceSequenceAction + 0x1F8)
};
