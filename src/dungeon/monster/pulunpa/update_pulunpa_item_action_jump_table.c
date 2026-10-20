#include "common.h"

extern void func_80175480(void);

/* jump_table; owner: dungeon/func_80CC1C80. */
const u32 D_80170888[7] __attribute__((aligned(4))) = {
    (u32)((u8 *)func_80175480 + 0x11C),
    (u32)((u8 *)func_80175480 + 0x114),
    (u32)((u8 *)func_80175480 + 0x10C),
    (u32)((u8 *)func_80175480 + 0x124),
    (u32)((u8 *)func_80175480 + 0xCC),
    (u32)((u8 *)func_80175480 + 0xC4),
    (u32)((u8 *)func_80175480 + 0xBC)
};
