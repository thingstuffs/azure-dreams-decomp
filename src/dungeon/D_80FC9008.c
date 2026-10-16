#include "common.h"

extern void dungeonUpdateActorSpecialAction(void);

/* jump_table; owner: dungeon/func_80FC976C. */
const u32 D_80158808[5] __attribute__((aligned(4))) = {
    (u32)((u8 *)dungeonUpdateActorSpecialAction + 0x1C0),
    (u32)((u8 *)dungeonUpdateActorSpecialAction + 0x22C),
    (u32)((u8 *)dungeonUpdateActorSpecialAction + 0x300),
    (u32)((u8 *)dungeonUpdateActorSpecialAction + 0x490),
    (u32)((u8 *)dungeonUpdateActorSpecialAction + 0x4D8)
};
