#include "common.h"

extern void func_8016DE64(void);

/* jump_table; owner: dungeon/func_8100E664. */
const u32 D_8016A878[5] __attribute__((aligned(4))) = {
    (u32)((u8 *)func_8016DE64 + 0x7C),
    (u32)((u8 *)func_8016DE64 + 0x294),
    (u32)((u8 *)func_8016DE64 + 0x3A0),
    (u32)((u8 *)func_8016DE64 + 0x694),
    (u32)((u8 *)func_8016DE64 + 0x804)
};
