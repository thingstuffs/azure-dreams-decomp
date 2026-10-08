#include "common.h"

extern void func_80170EA8(void);

/* Exact jump_table span; dispatch consumer dungeon/func_80FDB6A8. */
const u32 D_80170808[12] __attribute__((aligned(4))) = {
    (u32)((u8 *)func_80170EA8 + 0x410),
    (u32)((u8 *)func_80170EA8 + 0x410),
    (u32)((u8 *)func_80170EA8 + 0x410),
    (u32)((u8 *)func_80170EA8 + 0x43C),
    (u32)((u8 *)func_80170EA8 + 0x3BC),
    (u32)((u8 *)func_80170EA8 + 0x3BC),
    (u32)((u8 *)func_80170EA8 + 0x3BC),
    (u32)((u8 *)func_80170EA8 + 0x34C),
    (u32)((u8 *)func_80170EA8 + 0x33C),
    (u32)((u8 *)func_80170EA8 + 0x43C),
    (u32)((u8 *)func_80170EA8 + 0x43C),
    (u32)((u8 *)func_80170EA8 + 0x400)
};
