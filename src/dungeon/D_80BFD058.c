#include "common.h"

extern void func_80161CEC(void);

/* jump_table; owner: dungeon/func_80C004EC. */
const u32 D_8015E858[8] __attribute__((aligned(4))) = {
    (u32)((u8 *)func_80161CEC + 0x60),
    (u32)((u8 *)func_80161CEC + 0x74),
    (u32)((u8 *)func_80161CEC + 0xB8),
    (u32)((u8 *)func_80161CEC + 0x198),
    (u32)((u8 *)func_80161CEC + 0x26C),
    (u32)((u8 *)func_80161CEC + 0x3D0),
    (u32)((u8 *)func_80161CEC + 0x46C),
    (u32)((u8 *)func_80161CEC + 0x4EC)
};
