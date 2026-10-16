#include "common.h"

extern void dungeonUpdateActorItemAction(void);

/* jump_table; owner: dungeon/func_80F05FB0. */
const u32 D_8014C8A0[7] __attribute__((aligned(4))) = {
    (u32)((u8 *)dungeonUpdateActorItemAction + 0x110),
    (u32)((u8 *)dungeonUpdateActorItemAction + 0x108),
    (u32)((u8 *)dungeonUpdateActorItemAction + 0x100),
    (u32)((u8 *)dungeonUpdateActorItemAction + 0x118),
    (u32)((u8 *)dungeonUpdateActorItemAction + 0xBC),
    (u32)((u8 *)dungeonUpdateActorItemAction + 0xB4),
    (u32)((u8 *)dungeonUpdateActorItemAction + 0xAC)
};
