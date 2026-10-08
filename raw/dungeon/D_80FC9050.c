#include "common.h"

extern void func_8015ADEC(void);

/* jump_table; owner: dungeon/func_80FCB5EC. */
const u32 D_80158850[7] __attribute__((aligned(4))) = {
    (u32)((u8 *)func_8015ADEC + 0x11C),
    (u32)((u8 *)func_8015ADEC + 0x114),
    (u32)((u8 *)func_8015ADEC + 0x10C),
    (u32)((u8 *)func_8015ADEC + 0x124),
    (u32)((u8 *)func_8015ADEC + 0xCC),
    (u32)((u8 *)func_8015ADEC + 0xC4),
    (u32)((u8 *)func_8015ADEC + 0xBC)
};
