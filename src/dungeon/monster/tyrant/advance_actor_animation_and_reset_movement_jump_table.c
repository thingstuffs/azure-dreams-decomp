#include "common.h"

extern void advance_actor_animation_and_reset_movement(void);

/* jump_table; owner: dungeon/func_8107F1D4. */
const void *const tyrant_slot_a_action_targets[7] __attribute__((aligned(4))) = {
    ((u8 *)advance_actor_animation_and_reset_movement + 0x11C),
    ((u8 *)advance_actor_animation_and_reset_movement + 0x114),
    ((u8 *)advance_actor_animation_and_reset_movement + 0x10C),
    ((u8 *)advance_actor_animation_and_reset_movement + 0x124),
    ((u8 *)advance_actor_animation_and_reset_movement + 0xCC),
    ((u8 *)advance_actor_animation_and_reset_movement + 0xC4),
    ((u8 *)advance_actor_animation_and_reset_movement + 0xBC)
};
