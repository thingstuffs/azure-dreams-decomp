#include "common.h"

extern void advance_actor_action_phase_and_completion(void);

/* jump_table; owner: dungeon/func_81258D6C. */
const u32 D_8016A860[7] __attribute__((aligned(4))) = {
    (u32)((u8 *)advance_actor_action_phase_and_completion + 0x114),
    (u32)((u8 *)advance_actor_action_phase_and_completion + 0x10C),
    (u32)((u8 *)advance_actor_action_phase_and_completion + 0x104),
    (u32)((u8 *)advance_actor_action_phase_and_completion + 0x11C),
    (u32)((u8 *)advance_actor_action_phase_and_completion + 0xC0),
    (u32)((u8 *)advance_actor_action_phase_and_completion + 0xB8),
    (u32)((u8 *)advance_actor_action_phase_and_completion + 0xB0)
};
