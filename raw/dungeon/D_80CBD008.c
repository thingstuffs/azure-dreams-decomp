#include "common.h"

extern void func_80170F20(void);

/* jump_table; owner: dungeon/func_80CBD720. */
const u32 D_80170808[12] __attribute__((aligned(4))) = {
    (u32)((u8 *)func_80170F20 + 0x3C8),
    (u32)((u8 *)func_80170F20 + 0x3C8),
    (u32)((u8 *)func_80170F20 + 0x3C8),
    (u32)((u8 *)func_80170F20 + 0x3F4),
    (u32)((u8 *)func_80170F20 + 0x374),
    (u32)((u8 *)func_80170F20 + 0x374),
    (u32)((u8 *)func_80170F20 + 0x374),
    (u32)((u8 *)func_80170F20 + 0x33C),
    (u32)((u8 *)func_80170F20 + 0x33C),
    (u32)((u8 *)func_80170F20 + 0x3F4),
    (u32)((u8 *)func_80170F20 + 0x3F4),
    (u32)((u8 *)func_80170F20 + 0x3B8)
};
