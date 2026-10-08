#include "common.h"

extern void func_8014F514(void);

/* jump_table; owner: dungeon/func_80F05D14. */
const u32 D_8014C870[5] __attribute__((aligned(4))) = {
    (u32)((u8 *)func_8014F514 + 0x48),
    (u32)((u8 *)func_8014F514 + 0xD4),
    (u32)((u8 *)func_8014F514 + 0x118),
    (u32)((u8 *)func_8014F514 + 0x178),
    (u32)((u8 *)func_8014F514 + 0x23C)
};
