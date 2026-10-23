#include "common.h"

extern void advance_actor_animation_and_reset_motion(void);

/* jump_table; owner: dungeon/func_8106D1D4. */
const u32 tyrant_slot_d_action_targets[7] __attribute__((aligned(4))) = {
    (u32)((u8 *)advance_actor_animation_and_reset_motion + 0x11C),
    (u32)((u8 *)advance_actor_animation_and_reset_motion + 0x114),
    (u32)((u8 *)advance_actor_animation_and_reset_motion + 0x10C),
    (u32)((u8 *)advance_actor_animation_and_reset_motion + 0x124),
    (u32)((u8 *)advance_actor_animation_and_reset_motion + 0xCC),
    (u32)((u8 *)advance_actor_animation_and_reset_motion + 0xC4),
    (u32)((u8 *)advance_actor_animation_and_reset_motion + 0xBC)
};
