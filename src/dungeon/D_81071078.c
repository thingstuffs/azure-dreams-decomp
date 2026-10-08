#include "common.h"

extern void func_8015BC5C(void);

/* jump_table; owner: dungeon/func_8107445C. */
const u32 D_80158878[8] __attribute__((aligned(4))) = {
    (u32)((u8 *)func_8015BC5C + 0x60),
    (u32)((u8 *)func_8015BC5C + 0x104),
    (u32)((u8 *)func_8015BC5C + 0x17C),
    (u32)((u8 *)func_8015BC5C + 0x1B4),
    (u32)((u8 *)func_8015BC5C + 0x60),
    (u32)((u8 *)func_8015BC5C + 0x104),
    (u32)((u8 *)func_8015BC5C + 0x17C),
    (u32)((u8 *)func_8015BC5C + 0x214)
};
