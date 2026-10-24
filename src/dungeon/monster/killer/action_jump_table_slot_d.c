#include "common.h"

extern void func_801609A0(void);

/* jump_table; owner: dungeon/func_80FEF1A0. */
const void *const killer_slot_d_action_targets[7] __attribute__((aligned(4))) = {
    ((u8 *)func_801609A0 + 0x124),
    ((u8 *)func_801609A0 + 0x11C),
    ((u8 *)func_801609A0 + 0x114),
    ((u8 *)func_801609A0 + 0x12C),
    ((u8 *)func_801609A0 + 0xD4),
    ((u8 *)func_801609A0 + 0xCC),
    ((u8 *)func_801609A0 + 0xC4)
};
