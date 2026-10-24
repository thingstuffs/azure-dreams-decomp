#include "common.h"

extern void update_action_movement_landing_and_recovery(void);

/* jump_table; owner: dungeon/func_80E93490. */
const void *const picket_slot_f_action_targets[17] __attribute__((aligned(4))) = {
    ((u8 *)update_action_movement_landing_and_recovery + 0xA0),
    ((u8 *)update_action_movement_landing_and_recovery + 0x364),
    ((u8 *)update_action_movement_landing_and_recovery + 0x3E4),
    ((u8 *)update_action_movement_landing_and_recovery + 0x428),
    ((u8 *)update_action_movement_landing_and_recovery + 0x48C),
    ((u8 *)update_action_movement_landing_and_recovery + 0x558),
    ((u8 *)update_action_movement_landing_and_recovery + 0x604),
    ((u8 *)update_action_movement_landing_and_recovery + 0x760),
    ((u8 *)update_action_movement_landing_and_recovery + 0x760),
    ((u8 *)update_action_movement_landing_and_recovery + 0x760),
    ((u8 *)update_action_movement_landing_and_recovery + 0x760),
    ((u8 *)update_action_movement_landing_and_recovery + 0x760),
    ((u8 *)update_action_movement_landing_and_recovery + 0x760),
    ((u8 *)update_action_movement_landing_and_recovery + 0x760),
    ((u8 *)update_action_movement_landing_and_recovery + 0x760),
    ((u8 *)update_action_movement_landing_and_recovery + 0x760),
    ((u8 *)update_action_movement_landing_and_recovery + 0x674)
};
