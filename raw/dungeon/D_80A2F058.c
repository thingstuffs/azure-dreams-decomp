#include "common.h"

extern void func_801608C4(void);

/* jump_table; owner: dungeon/func_80A310C4. */
const u32 D_8015E858[7] __attribute__((aligned(4))) = {
    (u32)((u8 *)func_801608C4 + 0x128),
    (u32)((u8 *)func_801608C4 + 0x120),
    (u32)((u8 *)func_801608C4 + 0x118),
    (u32)((u8 *)func_801608C4 + 0x130),
    (u32)((u8 *)func_801608C4 + 0xD8),
    (u32)((u8 *)func_801608C4 + 0xD0),
    (u32)((u8 *)func_801608C4 + 0xC8)
};
