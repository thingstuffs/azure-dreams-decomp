#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

extern void start_actor_action_and_reset(void *action_state, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor);

/* jump_table; owner: dungeon/func_8102B034. */
const void *const D_8014C858[7] __attribute__((aligned(4))) = {
    ((u8 *)start_actor_action_and_reset + 0x11C),
    ((u8 *)start_actor_action_and_reset + 0x114),
    ((u8 *)start_actor_action_and_reset + 0x10C),
    ((u8 *)start_actor_action_and_reset + 0x124),
    ((u8 *)start_actor_action_and_reset + 0xCC),
    ((u8 *)start_actor_action_and_reset + 0xC4),
    ((u8 *)start_actor_action_and_reset + 0xBC)
};
