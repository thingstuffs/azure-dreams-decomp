#include "common.h"

extern void func_8016AF6C(void);

/* jump_table; owner: dungeon/func_80FB776C. */
const u32 D_8016A808[5] __attribute__((aligned(4))) = {
    (u32)((u8 *)func_8016AF6C + 0x1C0),
    (u32)((u8 *)func_8016AF6C + 0x22C),
    (u32)((u8 *)func_8016AF6C + 0x300),
    (u32)((u8 *)func_8016AF6C + 0x490),
    (u32)((u8 *)func_8016AF6C + 0x4D8)
};
