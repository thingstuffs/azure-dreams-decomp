#include "common.h"

extern void func_8014EFD8(void);

/* jump_table; owner: dungeon/func_80AEB7D8. */
const u32 D_8014C838[5] __attribute__((aligned(4))) = {
    (u32)((u8 *)func_8014EFD8 + 0x48),
    (u32)((u8 *)func_8014EFD8 + 0x98),
    (u32)((u8 *)func_8014EFD8 + 0x10C),
    (u32)((u8 *)func_8014EFD8 + 0x180),
    (u32)((u8 *)func_8014EFD8 + 0x1F8)
};
