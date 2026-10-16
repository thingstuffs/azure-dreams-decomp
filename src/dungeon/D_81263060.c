#include "common.h"

extern void dungeonAdvanceOverlayActorAction(void);

/* jump_table; owner: dungeon/func_81264D6C. */
const u32 D_8015E860[7] __attribute__((aligned(4))) = {
    (u32)((u8 *)dungeonAdvanceOverlayActorAction + 0x114),
    (u32)((u8 *)dungeonAdvanceOverlayActorAction + 0x10C),
    (u32)((u8 *)dungeonAdvanceOverlayActorAction + 0x104),
    (u32)((u8 *)dungeonAdvanceOverlayActorAction + 0x11C),
    (u32)((u8 *)dungeonAdvanceOverlayActorAction + 0xC0),
    (u32)((u8 *)dungeonAdvanceOverlayActorAction + 0xB8),
    (u32)((u8 *)dungeonAdvanceOverlayActorAction + 0xB0)
};
