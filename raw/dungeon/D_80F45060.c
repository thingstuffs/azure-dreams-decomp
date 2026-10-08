#include "common.h"

extern void func_801607B4(void);

/* jump_table; owner: dungeon/func_80F46FB4. */
const u32 D_8015E860[6] __attribute__((aligned(4))) = {
    (u32)((u8 *)func_801607B4 + 0x100),
    (u32)((u8 *)func_801607B4 + 0x208),
    (u32)((u8 *)func_801607B4 + 0x270),
    (u32)((u8 *)func_801607B4 + 0x30C),
    (u32)((u8 *)func_801607B4 + 0x5DC),
    (u32)((u8 *)func_801607B4 + 0x660)
};
