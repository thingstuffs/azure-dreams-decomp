#include "common.h"

extern void func_8015B64C(void);

/* jump_table; owner: dungeon/func_80D2BE4C. */
const u32 D_80158858[7] __attribute__((aligned(4))) = {
    (u32)((u8 *)func_8015B64C + 0x120),
    (u32)((u8 *)func_8015B64C + 0x118),
    (u32)((u8 *)func_8015B64C + 0x110),
    (u32)((u8 *)func_8015B64C + 0x128),
    (u32)((u8 *)func_8015B64C + 0xD0),
    (u32)((u8 *)func_8015B64C + 0xC8),
    (u32)((u8 *)func_8015B64C + 0xC0)
};
