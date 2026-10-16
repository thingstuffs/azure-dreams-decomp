#include "common.h"

extern void updateDungeonEntityActionAndFacing(void);

/* jump_table; owner: dungeon/func_80FE16A8. */
const u32 D_8016A808[12] __attribute__((aligned(4))) = {
    (u32)((u8 *)updateDungeonEntityActionAndFacing + 0x410),
    (u32)((u8 *)updateDungeonEntityActionAndFacing + 0x410),
    (u32)((u8 *)updateDungeonEntityActionAndFacing + 0x410),
    (u32)((u8 *)updateDungeonEntityActionAndFacing + 0x43C),
    (u32)((u8 *)updateDungeonEntityActionAndFacing + 0x3BC),
    (u32)((u8 *)updateDungeonEntityActionAndFacing + 0x3BC),
    (u32)((u8 *)updateDungeonEntityActionAndFacing + 0x3BC),
    (u32)((u8 *)updateDungeonEntityActionAndFacing + 0x34C),
    (u32)((u8 *)updateDungeonEntityActionAndFacing + 0x33C),
    (u32)((u8 *)updateDungeonEntityActionAndFacing + 0x43C),
    (u32)((u8 *)updateDungeonEntityActionAndFacing + 0x43C),
    (u32)((u8 *)updateDungeonEntityActionAndFacing + 0x400)
};
