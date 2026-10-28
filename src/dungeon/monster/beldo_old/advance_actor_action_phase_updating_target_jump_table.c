#include "common.h"
#include "shared/sprite_frame_state.h"

extern void advance_an_actor_s_action_phase_updating_target_animation_completion(void *action, void *motion, SpriteFrameState *sprite, void *actor);

/* jump_table; owner: dungeon/func_8127CD6C. */
const void *const D_8016F838[9] __attribute__((aligned(4))) = {
    ((u8 *)advance_an_actor_s_action_phase_updating_target_animation_completion + 0x64),
    ((u8 *)advance_an_actor_s_action_phase_updating_target_animation_completion + 0x2A8),
    ((u8 *)advance_an_actor_s_action_phase_updating_target_animation_completion + 0x2F0),
    ((u8 *)advance_an_actor_s_action_phase_updating_target_animation_completion + 0x330),
    ((u8 *)advance_an_actor_s_action_phase_updating_target_animation_completion + 0x3D0),
    ((u8 *)advance_an_actor_s_action_phase_updating_target_animation_completion + 0x43C),
    ((u8 *)advance_an_actor_s_action_phase_updating_target_animation_completion + 0x4A4),
    ((u8 *)advance_an_actor_s_action_phase_updating_target_animation_completion + 0x4C4),
    ((u8 *)advance_an_actor_s_action_phase_updating_target_animation_completion + 0x558)
};
