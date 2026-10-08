#include "common.h"

extern void func_8014E834(void);

/* jump_table; owner: dungeon/func_8102B034. */
const u32 D_8014C858[7] __attribute__((aligned(4))) = {
    (u32)((u8 *)func_8014E834 + 0x11C),
    (u32)((u8 *)func_8014E834 + 0x114),
    (u32)((u8 *)func_8014E834 + 0x10C),
    (u32)((u8 *)func_8014E834 + 0x124),
    (u32)((u8 *)func_8014E834 + 0xCC),
    (u32)((u8 *)func_8014E834 + 0xC4),
    (u32)((u8 *)func_8014E834 + 0xBC)
};
