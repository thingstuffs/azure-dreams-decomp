#include "common.h"

extern void func_8016CDEC(void);

/* jump_table; owner: dungeon/func_80FB95EC. */
const u32 D_8016A850[7] __attribute__((aligned(4))) = {
    (u32)((u8 *)func_8016CDEC + 0x11C),
    (u32)((u8 *)func_8016CDEC + 0x114),
    (u32)((u8 *)func_8016CDEC + 0x10C),
    (u32)((u8 *)func_8016CDEC + 0x124),
    (u32)((u8 *)func_8016CDEC + 0xCC),
    (u32)((u8 *)func_8016CDEC + 0xC4),
    (u32)((u8 *)func_8016CDEC + 0xBC)
};
