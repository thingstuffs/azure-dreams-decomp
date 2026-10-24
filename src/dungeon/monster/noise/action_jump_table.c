#include "common.h"

extern void func_8016D64C(void);

/* jump_table; owner: dungeon/func_80D19E4C. */
const void *const noise_slot_f_action_cases[7] __attribute__((aligned(4))) = {
    ((u8 *)func_8016D64C + 0x120),
    ((u8 *)func_8016D64C + 0x118),
    ((u8 *)func_8016D64C + 0x110),
    ((u8 *)func_8016D64C + 0x128),
    ((u8 *)func_8016D64C + 0xD0),
    ((u8 *)func_8016D64C + 0xC8),
    ((u8 *)func_8016D64C + 0xC0)
};
