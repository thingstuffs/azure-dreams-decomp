#include "common.h"

extern void func_8014F7B0(void);

/* jump_table; owner: dungeon/func_80F05FB0. */
const u32 D_8014C888[5] __attribute__((aligned(4))) = {
    (u32)((u8 *)func_8014F7B0 + 0x60),
    (u32)((u8 *)func_8014F7B0 + 0x298),
    (u32)((u8 *)func_8014F7B0 + 0x2E0),
    (u32)((u8 *)func_8014F7B0 + 0x434),
    (u32)((u8 *)func_8014F7B0 + 0x448)
};
