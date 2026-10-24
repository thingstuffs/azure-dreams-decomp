#include "common.h"

extern void advance_actor_animation_and_reset_motion(void);

/* jump_table; owner: dungeon/func_8106D1D4. */
const void *const tyrant_slot_d_action_targets[7] __attribute__((aligned(4))) = {
    ((u8 *)advance_actor_animation_and_reset_motion + 0x11C),
    ((u8 *)advance_actor_animation_and_reset_motion + 0x114),
    ((u8 *)advance_actor_animation_and_reset_motion + 0x10C),
    ((u8 *)advance_actor_animation_and_reset_motion + 0x124),
    ((u8 *)advance_actor_animation_and_reset_motion + 0xCC),
    ((u8 *)advance_actor_animation_and_reset_motion + 0xC4),
    ((u8 *)advance_actor_animation_and_reset_motion + 0xBC)
};
