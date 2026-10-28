#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

extern void advance_actor_action_sequence(ActorRecord *sequence, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor);

/* jump_table; owner: dungeon/func_80ADF7D8. */
const void *const saber_slot_c_action_targets[5] __attribute__((aligned(4))) = {
    ((u8 *)advance_actor_action_sequence + 0x48),
    ((u8 *)advance_actor_action_sequence + 0x98),
    ((u8 *)advance_actor_action_sequence + 0x10C),
    ((u8 *)advance_actor_action_sequence + 0x180),
    ((u8 *)advance_actor_action_sequence + 0x1F8)
};
