#include "common.h"

extern void func_80025408(void *, void *, void *);

/* jump_table; owner: dungeon/func_81917C08 (func_80025408 phase switch, lui/addiu 0x80024008 at +0x54). */
const u32 D_80024008[7] __attribute__((aligned(4))) = {
    (u32)((u8 *)func_80025408 + 0x74),
    (u32)((u8 *)func_80025408 + 0xBC),
    (u32)((u8 *)func_80025408 + 0x3D4),
    (u32)((u8 *)func_80025408 + 0x4A4),
    (u32)((u8 *)func_80025408 + 0x5D8),
    (u32)((u8 *)func_80025408 + 0x624),
    (u32)((u8 *)func_80025408 + 0x69C),
};
