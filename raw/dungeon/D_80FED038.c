#include "common.h"

extern void func_801609A0(void);

/* jump_table; owner: dungeon/func_80FEF1A0. */
const u32 D_8015E838[7] __attribute__((aligned(4))) = {
    (u32)((u8 *)func_801609A0 + 0x124),
    (u32)((u8 *)func_801609A0 + 0x11C),
    (u32)((u8 *)func_801609A0 + 0x114),
    (u32)((u8 *)func_801609A0 + 0x12C),
    (u32)((u8 *)func_801609A0 + 0xD4),
    (u32)((u8 *)func_801609A0 + 0xCC),
    (u32)((u8 *)func_801609A0 + 0xC4)
};
