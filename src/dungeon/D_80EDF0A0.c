#include "common.h"

extern void dungeonUpdateActorTargetedAction(void);

/* jump_table; owner: dungeon/func_80EE1FB0. */
const u32 D_801708A0[7] __attribute__((aligned(4))) = {
    (u32)((u8 *)dungeonUpdateActorTargetedAction + 0x110),
    (u32)((u8 *)dungeonUpdateActorTargetedAction + 0x108),
    (u32)((u8 *)dungeonUpdateActorTargetedAction + 0x100),
    (u32)((u8 *)dungeonUpdateActorTargetedAction + 0x118),
    (u32)((u8 *)dungeonUpdateActorTargetedAction + 0xBC),
    (u32)((u8 *)dungeonUpdateActorTargetedAction + 0xB4),
    (u32)((u8 *)dungeonUpdateActorTargetedAction + 0xAC)
};
