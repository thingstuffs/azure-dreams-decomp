#include "common.h"

extern void func_80161230(void);

/* jump_table; owner: dungeon/func_80AD9A30. */
const u32 D_8015E850[5] __attribute__((aligned(4))) = {
    (u32)((u8 *)func_80161230 + 0x6C),
    (u32)((u8 *)func_80161230 + 0x29C),
    (u32)((u8 *)func_80161230 + 0x2E4),
    (u32)((u8 *)func_80161230 + 0x514),
    (u32)((u8 *)func_80161230 + 0x59C)
};
