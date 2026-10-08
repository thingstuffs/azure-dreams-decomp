#include "common.h"

extern void func_80173514(void);

/* jump_table; owner: dungeon/func_80EE1D14. */
const u32 D_80170870[5] __attribute__((aligned(4))) = {
    (u32)((u8 *)func_80173514 + 0x48),
    (u32)((u8 *)func_80173514 + 0xD4),
    (u32)((u8 *)func_80173514 + 0x118),
    (u32)((u8 *)func_80173514 + 0x178),
    (u32)((u8 *)func_80173514 + 0x23C)
};
