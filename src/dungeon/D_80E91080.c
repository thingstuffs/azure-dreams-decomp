#include "common.h"

extern void update_action_movement_landing_and_recovery(void);

/* jump_table; owner: dungeon/func_80E93490. */
const u32 D_8016A880[7] __attribute__((aligned(4))) = {
    (u32)((u8 *)update_action_movement_landing_and_recovery + 0x15C),
    (u32)((u8 *)update_action_movement_landing_and_recovery + 0x154),
    (u32)((u8 *)update_action_movement_landing_and_recovery + 0x14C),
    (u32)((u8 *)update_action_movement_landing_and_recovery + 0x164),
    (u32)((u8 *)update_action_movement_landing_and_recovery + 0x108),
    (u32)((u8 *)update_action_movement_landing_and_recovery + 0x100),
    (u32)((u8 *)update_action_movement_landing_and_recovery + 0xF8)
};
