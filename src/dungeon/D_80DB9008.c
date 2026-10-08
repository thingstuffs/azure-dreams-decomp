#include "common.h"

extern void func_80171E20(void);

/* Exact jump_table span; dispatch consumer dungeon/func_80DBA620. */
const u32 D_80170808[12] __attribute__((aligned(4))) = {
    (u32)((u8 *)func_80171E20 + 0x3E4),
    (u32)((u8 *)func_80171E20 + 0x3E4),
    (u32)((u8 *)func_80171E20 + 0x3E4),
    (u32)((u8 *)func_80171E20 + 0x410),
    (u32)((u8 *)func_80171E20 + 0x390),
    (u32)((u8 *)func_80171E20 + 0x390),
    (u32)((u8 *)func_80171E20 + 0x390),
    (u32)((u8 *)func_80171E20 + 0x33C),
    (u32)((u8 *)func_80171E20 + 0x374),
    (u32)((u8 *)func_80171E20 + 0x410),
    (u32)((u8 *)func_80171E20 + 0x410),
    (u32)((u8 *)func_80171E20 + 0x3D4)
};
