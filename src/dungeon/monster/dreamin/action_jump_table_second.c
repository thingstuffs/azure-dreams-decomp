#include "common.h"

extern void func_80154870(void);

/* jump_table; owner: dungeon/func_80DAF070. */
const void *const D_80152838[7] __attribute__((aligned(4))) = {
    ((u8 *)func_80154870 + 0x11C),
    ((u8 *)func_80154870 + 0x114),
    ((u8 *)func_80154870 + 0x10C),
    ((u8 *)func_80154870 + 0x124),
    ((u8 *)func_80154870 + 0xCC),
    ((u8 *)func_80154870 + 0xC4),
    ((u8 *)func_80154870 + 0xBC)
};
