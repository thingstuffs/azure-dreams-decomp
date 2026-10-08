#include "common.h"

extern void func_8016056C(void);

/* jump_table; owner: dungeon/func_81264D6C. */
const u32 D_8015E860[7] __attribute__((aligned(4))) = {
    (u32)((u8 *)func_8016056C + 0x114),
    (u32)((u8 *)func_8016056C + 0x10C),
    (u32)((u8 *)func_8016056C + 0x104),
    (u32)((u8 *)func_8016056C + 0x11C),
    (u32)((u8 *)func_8016056C + 0xC0),
    (u32)((u8 *)func_8016056C + 0xB8),
    (u32)((u8 *)func_8016056C + 0xB0)
};
