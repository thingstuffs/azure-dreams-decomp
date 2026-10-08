#include "common.h"

extern void func_80160C90(void);

/* jump_table; owner: dungeon/func_80E9F490. */
const u32 D_8015E880[7] __attribute__((aligned(4))) = {
    (u32)((u8 *)func_80160C90 + 0x15C),
    (u32)((u8 *)func_80160C90 + 0x154),
    (u32)((u8 *)func_80160C90 + 0x14C),
    (u32)((u8 *)func_80160C90 + 0x164),
    (u32)((u8 *)func_80160C90 + 0x108),
    (u32)((u8 *)func_80160C90 + 0x100),
    (u32)((u8 *)func_80160C90 + 0xF8)
};
