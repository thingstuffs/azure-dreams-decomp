#include "common.h"

extern void func_80170F6C(void);

/* Exact jump_table span; dispatch consumer dungeon/func_80FB176C. */
const u32 D_80170808[5] __attribute__((aligned(4))) = {
    (u32)((u8 *)func_80170F6C + 0x1C0),
    (u32)((u8 *)func_80170F6C + 0x22C),
    (u32)((u8 *)func_80170F6C + 0x300),
    (u32)((u8 *)func_80170F6C + 0x490),
    (u32)((u8 *)func_80170F6C + 0x4D8)
};
