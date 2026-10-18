#include "common.h"

extern void advance_action_and_activate_effect(void);

/* jump_table; owner: dungeon/func_80A310C4. */
const u32 D_8015E858[7] __attribute__((aligned(4))) = {
    (u32)((u8 *)advance_action_and_activate_effect + 0x128),
    (u32)((u8 *)advance_action_and_activate_effect + 0x120),
    (u32)((u8 *)advance_action_and_activate_effect + 0x118),
    (u32)((u8 *)advance_action_and_activate_effect + 0x130),
    (u32)((u8 *)advance_action_and_activate_effect + 0xD8),
    (u32)((u8 *)advance_action_and_activate_effect + 0xD0),
    (u32)((u8 *)advance_action_and_activate_effect + 0xC8)
};
