#include "common.h"

extern void advanceActorActionPhase(void);

/* jump_table; owner: dungeon/func_80EF9D14. */
const u32 D_80158870[5] __attribute__((aligned(4))) = {
    (u32)((u8 *)advanceActorActionPhase + 0x48),
    (u32)((u8 *)advanceActorActionPhase + 0xD4),
    (u32)((u8 *)advanceActorActionPhase + 0x118),
    (u32)((u8 *)advanceActorActionPhase + 0x178),
    (u32)((u8 *)advanceActorActionPhase + 0x23C)
};
