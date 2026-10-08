#include "common.h"

extern void func_8016D230(void);

/* jump_table; owner: dungeon/func_80ACDA30. */
const u32 D_8016A868[7] __attribute__((aligned(4))) = {
    (u32)((u8 *)func_8016D230 + 0x11C),
    (u32)((u8 *)func_8016D230 + 0x114),
    (u32)((u8 *)func_8016D230 + 0x10C),
    (u32)((u8 *)func_8016D230 + 0x124),
    (u32)((u8 *)func_8016D230 + 0xC8),
    (u32)((u8 *)func_8016D230 + 0xC0),
    (u32)((u8 *)func_8016D230 + 0xB8)
};
