#include "common.h"

extern void dungeonAdvanceVariantActorAction(void);

/* jump_table; owner: dungeon/func_8126AD6C. */
const u32 D_80158838[9] __attribute__((aligned(4))) = {
    (u32)((u8 *)dungeonAdvanceVariantActorAction + 0x64),
    (u32)((u8 *)dungeonAdvanceVariantActorAction + 0x2A8),
    (u32)((u8 *)dungeonAdvanceVariantActorAction + 0x2F0),
    (u32)((u8 *)dungeonAdvanceVariantActorAction + 0x330),
    (u32)((u8 *)dungeonAdvanceVariantActorAction + 0x3D0),
    (u32)((u8 *)dungeonAdvanceVariantActorAction + 0x43C),
    (u32)((u8 *)dungeonAdvanceVariantActorAction + 0x4A4),
    (u32)((u8 *)dungeonAdvanceVariantActorAction + 0x4C4),
    (u32)((u8 *)dungeonAdvanceVariantActorAction + 0x558)
};
