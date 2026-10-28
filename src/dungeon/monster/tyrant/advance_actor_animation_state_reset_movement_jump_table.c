#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

extern void advance_the_actor_animation_state_reset_movement_finishes_at_8015_a_9_d_4(ActorRecord *action, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor);

/* jump_table; owner: dungeon/func_810731D4. */
const void *const tyrant_slot_c_action_targets[7] __attribute__((aligned(4))) = {
    ((u8 *)advance_the_actor_animation_state_reset_movement_finishes_at_8015_a_9_d_4 + 0x11C),
    ((u8 *)advance_the_actor_animation_state_reset_movement_finishes_at_8015_a_9_d_4 + 0x114),
    ((u8 *)advance_the_actor_animation_state_reset_movement_finishes_at_8015_a_9_d_4 + 0x10C),
    ((u8 *)advance_the_actor_animation_state_reset_movement_finishes_at_8015_a_9_d_4 + 0x124),
    ((u8 *)advance_the_actor_animation_state_reset_movement_finishes_at_8015_a_9_d_4 + 0xCC),
    ((u8 *)advance_the_actor_animation_state_reset_movement_finishes_at_8015_a_9_d_4 + 0xC4),
    ((u8 *)advance_the_actor_animation_state_reset_movement_finishes_at_8015_a_9_d_4 + 0xBC)
};
