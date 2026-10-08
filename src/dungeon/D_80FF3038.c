#include "common.h"

extern void func_8015A9A0(void);

/* jump_table; owner: dungeon/func_80FF51A0. */
const u32 D_80158838[7] __attribute__((aligned(4))) = {
    (u32)((u8 *)func_8015A9A0 + 0x124),
    (u32)((u8 *)func_8015A9A0 + 0x11C),
    (u32)((u8 *)func_8015A9A0 + 0x114),
    (u32)((u8 *)func_8015A9A0 + 0x12C),
    (u32)((u8 *)func_8015A9A0 + 0xD4),
    (u32)((u8 *)func_8015A9A0 + 0xCC),
    (u32)((u8 *)func_8015A9A0 + 0xC4)
};
