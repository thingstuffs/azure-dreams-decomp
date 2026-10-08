#include "common.h"

extern void func_80166A40(void);

/* jump_table; owner: dungeon/func_80F95240. */
const u32 D_80164838[7] __attribute__((aligned(4))) = {
    (u32)((u8 *)func_80166A40 + 0x11C),
    (u32)((u8 *)func_80166A40 + 0x114),
    (u32)((u8 *)func_80166A40 + 0x10C),
    (u32)((u8 *)func_80166A40 + 0x124),
    (u32)((u8 *)func_80166A40 + 0xCC),
    (u32)((u8 *)func_80166A40 + 0xC4),
    (u32)((u8 *)func_80166A40 + 0xBC)
};
