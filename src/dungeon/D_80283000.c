#include "common.h"

extern void func_8001D4AC(void);

/* Exact jump_table span; dispatch consumer dungeon/func_8028A4AC. */
const u32 D_80016000[13] __attribute__((aligned(4))) = {
    (u32)((u8 *)func_8001D4AC + 0x50),
    (u32)((u8 *)func_8001D4AC + 0x5C),
    (u32)((u8 *)func_8001D4AC + 0x94),
    (u32)((u8 *)func_8001D4AC + 0x114),
    (u32)((u8 *)func_8001D4AC + 0xCC),
    (u32)((u8 *)func_8001D4AC + 0x104),
    (u32)((u8 *)func_8001D4AC + 0x104),
    (u32)((u8 *)func_8001D4AC + 0x104),
    (u32)((u8 *)func_8001D4AC + 0x104),
    (u32)((u8 *)func_8001D4AC + 0x104),
    (u32)((u8 *)func_8001D4AC + 0x104),
    (u32)((u8 *)func_8001D4AC + 0x104),
    (u32)((u8 *)func_8001D4AC + 0x104)
};
