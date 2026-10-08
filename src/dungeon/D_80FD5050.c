#include "common.h"

extern void func_8014EDEC(void);

/* jump_table; owner: dungeon/func_80FD75EC. */
const u32 D_8014C850[7] __attribute__((aligned(4))) = {
    (u32)((u8 *)func_8014EDEC + 0x11C),
    (u32)((u8 *)func_8014EDEC + 0x114),
    (u32)((u8 *)func_8014EDEC + 0x10C),
    (u32)((u8 *)func_8014EDEC + 0x124),
    (u32)((u8 *)func_8014EDEC + 0xCC),
    (u32)((u8 *)func_8014EDEC + 0xC4),
    (u32)((u8 *)func_8014EDEC + 0xBC)
};
