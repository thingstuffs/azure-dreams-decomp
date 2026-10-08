#include "common.h"

extern void func_8014EEC4(void);

/* jump_table; owner: dungeon/func_812776C4. */
const u32 D_8014C880[6] __attribute__((aligned(4))) = {
    (u32)((u8 *)func_8014EEC4 + 0x5C),
    (u32)((u8 *)func_8014EEC4 + 0xCC),
    (u32)((u8 *)func_8014EEC4 + 0xE4),
    (u32)((u8 *)func_8014EEC4 + 0x110),
    (u32)((u8 *)func_8014EEC4 + 0x38C),
    (u32)((u8 *)func_8014EEC4 + 0x3FC)
};
