#include "common.h"

extern void func_80161230(void);

/* jump_table; owner: dungeon/func_80AD9A30. */
const u32 D_8015E868[7] __attribute__((aligned(4))) = {
    (u32)((u8 *)func_80161230 + 0x11C),
    (u32)((u8 *)func_80161230 + 0x114),
    (u32)((u8 *)func_80161230 + 0x10C),
    (u32)((u8 *)func_80161230 + 0x124),
    (u32)((u8 *)func_80161230 + 0xC8),
    (u32)((u8 *)func_80161230 + 0xC0),
    (u32)((u8 *)func_80161230 + 0xB8)
};
