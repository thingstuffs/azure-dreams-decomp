#include "common.h"

extern void func_80152EA8(void);

/* jump_table; owner: dungeon/func_80FF96A8. */
const u32 D_80152808[12] __attribute__((aligned(4))) = {
    (u32)((u8 *)func_80152EA8 + 0x410),
    (u32)((u8 *)func_80152EA8 + 0x410),
    (u32)((u8 *)func_80152EA8 + 0x410),
    (u32)((u8 *)func_80152EA8 + 0x43C),
    (u32)((u8 *)func_80152EA8 + 0x3BC),
    (u32)((u8 *)func_80152EA8 + 0x3BC),
    (u32)((u8 *)func_80152EA8 + 0x3BC),
    (u32)((u8 *)func_80152EA8 + 0x34C),
    (u32)((u8 *)func_80152EA8 + 0x33C),
    (u32)((u8 *)func_80152EA8 + 0x43C),
    (u32)((u8 *)func_80152EA8 + 0x43C),
    (u32)((u8 *)func_80152EA8 + 0x400)
};
