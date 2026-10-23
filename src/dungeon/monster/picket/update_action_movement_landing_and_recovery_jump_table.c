#include "common.h"

extern void update_action_movement_landing_and_recovery(void);

/* jump_table; owner: dungeon/func_80E93490. */
const u32 picket_slot_f_action_targets[17] __attribute__((aligned(4))) = {
    (u32)((u8 *)update_action_movement_landing_and_recovery + 0xA0),
    (u32)((u8 *)update_action_movement_landing_and_recovery + 0x364),
    (u32)((u8 *)update_action_movement_landing_and_recovery + 0x3E4),
    (u32)((u8 *)update_action_movement_landing_and_recovery + 0x428),
    (u32)((u8 *)update_action_movement_landing_and_recovery + 0x48C),
    (u32)((u8 *)update_action_movement_landing_and_recovery + 0x558),
    (u32)((u8 *)update_action_movement_landing_and_recovery + 0x604),
    (u32)((u8 *)update_action_movement_landing_and_recovery + 0x760),
    (u32)((u8 *)update_action_movement_landing_and_recovery + 0x760),
    (u32)((u8 *)update_action_movement_landing_and_recovery + 0x760),
    (u32)((u8 *)update_action_movement_landing_and_recovery + 0x760),
    (u32)((u8 *)update_action_movement_landing_and_recovery + 0x760),
    (u32)((u8 *)update_action_movement_landing_and_recovery + 0x760),
    (u32)((u8 *)update_action_movement_landing_and_recovery + 0x760),
    (u32)((u8 *)update_action_movement_landing_and_recovery + 0x760),
    (u32)((u8 *)update_action_movement_landing_and_recovery + 0x760),
    (u32)((u8 *)update_action_movement_landing_and_recovery + 0x674)
};
