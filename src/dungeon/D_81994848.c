#include "common.h"

extern void func_8002458C(void *, void *, void *);

/* jump_table; owner: dungeon/func_81994D8C. */
const u32 D_80024048[5] __attribute__((aligned(4))) = {
    (u32)((u8 *)func_8002458C + 0x64),
    (u32)((u8 *)func_8002458C + 0xE8),
    (u32)((u8 *)func_8002458C + 0x200),
    (u32)((u8 *)func_8002458C + 0x80C),
    (u32)((u8 *)func_8002458C + 0xBA0)
};
