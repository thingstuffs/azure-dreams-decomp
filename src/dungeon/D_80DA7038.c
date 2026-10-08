#include "common.h"

extern void func_8015A870(void);

/* jump_table; owner: dungeon/func_80DA9070. */
const u32 D_80158838[7] __attribute__((aligned(4))) = {
    (u32)((u8 *)func_8015A870 + 0x11C),
    (u32)((u8 *)func_8015A870 + 0x114),
    (u32)((u8 *)func_8015A870 + 0x10C),
    (u32)((u8 *)func_8015A870 + 0x124),
    (u32)((u8 *)func_8015A870 + 0xCC),
    (u32)((u8 *)func_8015A870 + 0xC4),
    (u32)((u8 *)func_8015A870 + 0xBC)
};
