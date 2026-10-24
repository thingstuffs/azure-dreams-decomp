#include "common.h"

extern void func_8015BE64(void);

/* jump_table; owner: dungeon/func_81020664. */
const void *const D_80158878[5] __attribute__((aligned(4))) = {
    ((u8 *)func_8015BE64 + 0x7C),
    ((u8 *)func_8015BE64 + 0x294),
    ((u8 *)func_8015BE64 + 0x3A0),
    ((u8 *)func_8015BE64 + 0x694),
    ((u8 *)func_8015BE64 + 0x804)
};
