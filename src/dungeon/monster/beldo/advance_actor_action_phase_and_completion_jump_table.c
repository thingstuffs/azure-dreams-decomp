#include "common.h"
#include "shared/sprite_frame_state.h"

extern void advance_actor_action_phase_and_completion(void *action, void *motion, SpriteFrameState *sprite, void *actor);

/* jump_table; owner: dungeon/func_81258D6C. */
const void *const D_8016A860[7] __attribute__((aligned(4))) = {
    ((u8 *)advance_actor_action_phase_and_completion + 0x114),
    ((u8 *)advance_actor_action_phase_and_completion + 0x10C),
    ((u8 *)advance_actor_action_phase_and_completion + 0x104),
    ((u8 *)advance_actor_action_phase_and_completion + 0x11C),
    ((u8 *)advance_actor_action_phase_and_completion + 0xC0),
    ((u8 *)advance_actor_action_phase_and_completion + 0xB8),
    ((u8 *)advance_actor_action_phase_and_completion + 0xB0)
};
