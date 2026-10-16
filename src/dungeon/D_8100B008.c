#include "common.h"

extern void dungeonDispatchCreatureAction(void);

/* jump_table; owner: dungeon/func_8100B858. */
const u32 D_8016A808[12] __attribute__((aligned(4))) = {
    (u32)((u8 *)dungeonDispatchCreatureAction + 0x494),
    (u32)((u8 *)dungeonDispatchCreatureAction + 0x494),
    (u32)((u8 *)dungeonDispatchCreatureAction + 0x494),
    (u32)((u8 *)dungeonDispatchCreatureAction + 0x4C0),
    (u32)((u8 *)dungeonDispatchCreatureAction + 0x440),
    (u32)((u8 *)dungeonDispatchCreatureAction + 0x440),
    (u32)((u8 *)dungeonDispatchCreatureAction + 0x440),
    (u32)((u8 *)dungeonDispatchCreatureAction + 0x408),
    (u32)((u8 *)dungeonDispatchCreatureAction + 0x3AC),
    (u32)((u8 *)dungeonDispatchCreatureAction + 0x4C0),
    (u32)((u8 *)dungeonDispatchCreatureAction + 0x4C0),
    (u32)((u8 *)dungeonDispatchCreatureAction + 0x484)
};
