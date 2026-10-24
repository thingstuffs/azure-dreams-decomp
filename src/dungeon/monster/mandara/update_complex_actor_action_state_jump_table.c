#include "common.h"

extern void update_complex_actor_action_state(void);

/* jump_table; owner: dungeon/func_80FB776C. */
const void *const mandara_slot_f_behavior_targets[5] __attribute__((aligned(4))) = {
    ((u8 *)update_complex_actor_action_state + 0x1C0),
    ((u8 *)update_complex_actor_action_state + 0x22C),
    ((u8 *)update_complex_actor_action_state + 0x300),
    ((u8 *)update_complex_actor_action_state + 0x490),
    ((u8 *)update_complex_actor_action_state + 0x4D8)
};
