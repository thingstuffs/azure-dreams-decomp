#include "common.h"

extern void func_8015AC90(void);

/* jump_table; owner: dungeon/func_80EA5490. */
const u32 D_80158880[7] __attribute__((aligned(4))) = {
    (u32)((u8 *)func_8015AC90 + 0x15C),
    (u32)((u8 *)func_8015AC90 + 0x154),
    (u32)((u8 *)func_8015AC90 + 0x14C),
    (u32)((u8 *)func_8015AC90 + 0x164),
    (u32)((u8 *)func_8015AC90 + 0x108),
    (u32)((u8 *)func_8015AC90 + 0x100),
    (u32)((u8 *)func_8015AC90 + 0xF8)
};
