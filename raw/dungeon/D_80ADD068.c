#include "common.h"

extern void func_8015B230(void);

/* jump_table; owner: dungeon/func_80ADFA30. */
const u32 D_80158868[7] __attribute__((aligned(4))) = {
    (u32)((u8 *)func_8015B230 + 0x11C),
    (u32)((u8 *)func_8015B230 + 0x114),
    (u32)((u8 *)func_8015B230 + 0x10C),
    (u32)((u8 *)func_8015B230 + 0x124),
    (u32)((u8 *)func_8015B230 + 0xC8),
    (u32)((u8 *)func_8015B230 + 0xC0),
    (u32)((u8 *)func_8015B230 + 0xB8)
};
