#include "common.h"

extern void func_80160F5C(void);

/* jump_table; owner: dungeon/func_80F4775C. */
const u32 D_8015E878[7] __attribute__((aligned(4))) = {
    (u32)((u8 *)func_80160F5C + 0x11C),
    (u32)((u8 *)func_80160F5C + 0x114),
    (u32)((u8 *)func_80160F5C + 0x10C),
    (u32)((u8 *)func_80160F5C + 0x124),
    (u32)((u8 *)func_80160F5C + 0xCC),
    (u32)((u8 *)func_80160F5C + 0xC4),
    (u32)((u8 *)func_80160F5C + 0xBC)
};
