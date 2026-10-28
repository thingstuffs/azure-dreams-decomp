#include "common.h"
#include "shared/sprite_frame_state.h"

extern void advance_actor_action_phase(void *action, void *motion, SpriteFrameState *sprite, void *actor);

/* jump_table; owner: dungeon/func_81276D6C. */
const void *const D_8014C860[7] __attribute__((aligned(4))) = {
    ((u8 *)advance_actor_action_phase + 0x114),
    ((u8 *)advance_actor_action_phase + 0x10C),
    ((u8 *)advance_actor_action_phase + 0x104),
    ((u8 *)advance_actor_action_phase + 0x11C),
    ((u8 *)advance_actor_action_phase + 0xC0),
    ((u8 *)advance_actor_action_phase + 0xB8),
    ((u8 *)advance_actor_action_phase + 0xB0)
};
