#include "common.h"

extern void func_80172DEC(void);

/* Exact jump_table span; dispatch consumer dungeon/func_80FB35EC. */
const u32 D_80170850[7] __attribute__((aligned(4))) = {
    (u32)((u8 *)func_80172DEC + 0x11C),
    (u32)((u8 *)func_80172DEC + 0x114),
    (u32)((u8 *)func_80172DEC + 0x10C),
    (u32)((u8 *)func_80172DEC + 0x124),
    (u32)((u8 *)func_80172DEC + 0xCC),
    (u32)((u8 *)func_80172DEC + 0xC4),
    (u32)((u8 *)func_80172DEC + 0xBC)
};
