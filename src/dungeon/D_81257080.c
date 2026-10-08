#include "common.h"

extern void func_8016CEC4(void);

/* jump_table; owner: dungeon/func_812596C4. */
const u32 D_8016A880[6] __attribute__((aligned(4))) = {
    (u32)((u8 *)func_8016CEC4 + 0x5C),
    (u32)((u8 *)func_8016CEC4 + 0xCC),
    (u32)((u8 *)func_8016CEC4 + 0xE4),
    (u32)((u8 *)func_8016CEC4 + 0x110),
    (u32)((u8 *)func_8016CEC4 + 0x38C),
    (u32)((u8 *)func_8016CEC4 + 0x3FC)
};
