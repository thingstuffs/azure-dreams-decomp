#include "common.h"

extern void dungeonUpdateCreatureActionAndAnimation(void);

/* jump_table; owner: dungeon/func_80FD576C. */
const u32 D_8014C808[5] __attribute__((aligned(4))) = {
    (u32)((u8 *)dungeonUpdateCreatureActionAndAnimation + 0x1C0),
    (u32)((u8 *)dungeonUpdateCreatureActionAndAnimation + 0x22C),
    (u32)((u8 *)dungeonUpdateCreatureActionAndAnimation + 0x300),
    (u32)((u8 *)dungeonUpdateCreatureActionAndAnimation + 0x490),
    (u32)((u8 *)dungeonUpdateCreatureActionAndAnimation + 0x4D8)
};
