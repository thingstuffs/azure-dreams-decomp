#include "common.h"

extern void dungeonUpdateActorTargetedAction(void);

/* jump_table; owner: dungeon/func_80EE1FB0. */
const u32 D_80170888[5] __attribute__((aligned(4))) = {
    (u32)((u8 *)dungeonUpdateActorTargetedAction + 0x60),
    (u32)((u8 *)dungeonUpdateActorTargetedAction + 0x298),
    (u32)((u8 *)dungeonUpdateActorTargetedAction + 0x2E0),
    (u32)((u8 *)dungeonUpdateActorTargetedAction + 0x434),
    (u32)((u8 *)dungeonUpdateActorTargetedAction + 0x448)
};
