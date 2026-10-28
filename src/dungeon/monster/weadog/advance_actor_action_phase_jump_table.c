#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

extern void advance_actor_action_phase_2(ActorRecord *action, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor);

/* jump_table; owner: dungeon/func_80EF9D14. */
const void *const D_80158870[5] __attribute__((aligned(4))) = {
    ((u8 *)advance_actor_action_phase_2 + 0x48),
    ((u8 *)advance_actor_action_phase_2 + 0xD4),
    ((u8 *)advance_actor_action_phase_2 + 0x118),
    ((u8 *)advance_actor_action_phase_2 + 0x178),
    ((u8 *)advance_actor_action_phase_2 + 0x23C)
};
