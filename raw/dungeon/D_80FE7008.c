#include "common.h"

extern void func_80164EA8(void);

/* jump_table; owner: dungeon/func_80FE76A8. */
const u32 D_80164808[12] __attribute__((aligned(4))) = {
    (u32)((u8 *)func_80164EA8 + 0x410),
    (u32)((u8 *)func_80164EA8 + 0x410),
    (u32)((u8 *)func_80164EA8 + 0x410),
    (u32)((u8 *)func_80164EA8 + 0x43C),
    (u32)((u8 *)func_80164EA8 + 0x3BC),
    (u32)((u8 *)func_80164EA8 + 0x3BC),
    (u32)((u8 *)func_80164EA8 + 0x3BC),
    (u32)((u8 *)func_80164EA8 + 0x34C),
    (u32)((u8 *)func_80164EA8 + 0x33C),
    (u32)((u8 *)func_80164EA8 + 0x43C),
    (u32)((u8 *)func_80164EA8 + 0x43C),
    (u32)((u8 *)func_80164EA8 + 0x400)
};
