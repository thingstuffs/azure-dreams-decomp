#include "common.h"

extern void func_801617B0(void);

/* jump_table; owner: dungeon/func_80EF3FB0. */
const u32 D_8015E888[5] __attribute__((aligned(4))) = {
    (u32)((u8 *)func_801617B0 + 0x60),
    (u32)((u8 *)func_801617B0 + 0x298),
    (u32)((u8 *)func_801617B0 + 0x2E0),
    (u32)((u8 *)func_801617B0 + 0x434),
    (u32)((u8 *)func_801617B0 + 0x448)
};
