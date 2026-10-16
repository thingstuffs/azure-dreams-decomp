#include "common.h"

extern void dungeonRunSelectedActorAction(void);

/* jump_table; owner: dungeon/func_8101F034. */
const u32 D_80158858[7] __attribute__((aligned(4))) = {
    (u32)((u8 *)dungeonRunSelectedActorAction + 0x11C),
    (u32)((u8 *)dungeonRunSelectedActorAction + 0x114),
    (u32)((u8 *)dungeonRunSelectedActorAction + 0x10C),
    (u32)((u8 *)dungeonRunSelectedActorAction + 0x124),
    (u32)((u8 *)dungeonRunSelectedActorAction + 0xCC),
    (u32)((u8 *)dungeonRunSelectedActorAction + 0xC4),
    (u32)((u8 *)dungeonRunSelectedActorAction + 0xBC)
};
