#include "common.h"

extern void func_801617B0(void);

/* jump_table; owner: dungeon/func_80EF3FB0. */
const u32 D_8015E8A0[7] __attribute__((aligned(4))) = {
    (u32)((u8 *)func_801617B0 + 0x110),
    (u32)((u8 *)func_801617B0 + 0x108),
    (u32)((u8 *)func_801617B0 + 0x100),
    (u32)((u8 *)func_801617B0 + 0x118),
    (u32)((u8 *)func_801617B0 + 0xBC),
    (u32)((u8 *)func_801617B0 + 0xB4),
    (u32)((u8 *)func_801617B0 + 0xAC)
};
