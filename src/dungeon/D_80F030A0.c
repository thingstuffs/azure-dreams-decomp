#include "common.h"

extern void func_8014F7B0(void);

/* jump_table; owner: dungeon/func_80F05FB0. */
const u32 D_8014C8A0[7] __attribute__((aligned(4))) = {
    (u32)((u8 *)func_8014F7B0 + 0x110),
    (u32)((u8 *)func_8014F7B0 + 0x108),
    (u32)((u8 *)func_8014F7B0 + 0x100),
    (u32)((u8 *)func_8014F7B0 + 0x118),
    (u32)((u8 *)func_8014F7B0 + 0xBC),
    (u32)((u8 *)func_8014F7B0 + 0xB4),
    (u32)((u8 *)func_8014F7B0 + 0xAC)
};
