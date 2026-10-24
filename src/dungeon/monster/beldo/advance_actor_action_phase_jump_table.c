#include "common.h"

extern void advance_actor_action_phase(void);

/* jump_table; owner: dungeon/func_81276D6C. */
const void *const beldo_slot_a_action_targets[9] __attribute__((aligned(4))) = {
    ((u8 *)advance_actor_action_phase + 0x64),
    ((u8 *)advance_actor_action_phase + 0x2A8),
    ((u8 *)advance_actor_action_phase + 0x2F0),
    ((u8 *)advance_actor_action_phase + 0x330),
    ((u8 *)advance_actor_action_phase + 0x3D0),
    ((u8 *)advance_actor_action_phase + 0x43C),
    ((u8 *)advance_actor_action_phase + 0x4A4),
    ((u8 *)advance_actor_action_phase + 0x4C4),
    ((u8 *)advance_actor_action_phase + 0x558)
};
