#include "common.h"

extern void func_8016D230(void);

/* jump_table; owner: dungeon/func_80ACDA30. */
const u32 D_8016A850[5] __attribute__((aligned(4))) = {
    (u32)((u8 *)func_8016D230 + 0x6C),
    (u32)((u8 *)func_8016D230 + 0x29C),
    (u32)((u8 *)func_8016D230 + 0x2E4),
    (u32)((u8 *)func_8016D230 + 0x514),
    (u32)((u8 *)func_8016D230 + 0x59C)
};
