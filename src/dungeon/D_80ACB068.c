#include "common.h"

extern void dungeonUpdateThreeActionRecords(void);

/* jump_table; owner: dungeon/func_80ACDA30. */
const u32 D_8016A868[7] __attribute__((aligned(4))) = {
    (u32)((u8 *)dungeonUpdateThreeActionRecords + 0x11C),
    (u32)((u8 *)dungeonUpdateThreeActionRecords + 0x114),
    (u32)((u8 *)dungeonUpdateThreeActionRecords + 0x10C),
    (u32)((u8 *)dungeonUpdateThreeActionRecords + 0x124),
    (u32)((u8 *)dungeonUpdateThreeActionRecords + 0xC8),
    (u32)((u8 *)dungeonUpdateThreeActionRecords + 0xC0),
    (u32)((u8 *)dungeonUpdateThreeActionRecords + 0xB8)
};
