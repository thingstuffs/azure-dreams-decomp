#include "common.h"

extern void func_80154870(void);

/* jump_table; owner: dungeon/func_80DAF070. */
const u32 D_80152838[7] __attribute__((aligned(4))) = {
    (u32)((u8 *)func_80154870 + 0x11C),
    (u32)((u8 *)func_80154870 + 0x114),
    (u32)((u8 *)func_80154870 + 0x10C),
    (u32)((u8 *)func_80154870 + 0x124),
    (u32)((u8 *)func_80154870 + 0xCC),
    (u32)((u8 *)func_80154870 + 0xC4),
    (u32)((u8 *)func_80154870 + 0xBC)
};
