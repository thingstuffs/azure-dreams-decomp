#include "common.h"

extern void advance_actor_action_phase(void);

/* jump_table; owner: dungeon/func_81276D6C. */
const u32 beldo_slot_a_action_targets_b[9] __attribute__((aligned(4))) = {
    (u32)((u8 *)advance_actor_action_phase + 0x64),
    (u32)((u8 *)advance_actor_action_phase + 0x2A8),
    (u32)((u8 *)advance_actor_action_phase + 0x2F0),
    (u32)((u8 *)advance_actor_action_phase + 0x330),
    (u32)((u8 *)advance_actor_action_phase + 0x3D0),
    (u32)((u8 *)advance_actor_action_phase + 0x43C),
    (u32)((u8 *)advance_actor_action_phase + 0x4A4),
    (u32)((u8 *)advance_actor_action_phase + 0x4C4),
    (u32)((u8 *)advance_actor_action_phase + 0x558)
};
