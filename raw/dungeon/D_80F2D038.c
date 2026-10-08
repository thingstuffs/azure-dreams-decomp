#include "common.h"

extern void func_8014EAA8(void);

/* jump_table; owner: dungeon/func_80F2F2A8. */
const u32 D_8014C838[7] __attribute__((aligned(4))) = {
    (u32)((u8 *)func_8014EAA8 + 0x11C),
    (u32)((u8 *)func_8014EAA8 + 0x114),
    (u32)((u8 *)func_8014EAA8 + 0x10C),
    (u32)((u8 *)func_8014EAA8 + 0x124),
    (u32)((u8 *)func_8014EAA8 + 0xCC),
    (u32)((u8 *)func_8014EAA8 + 0xC4),
    (u32)((u8 *)func_8014EAA8 + 0xBC)
};
