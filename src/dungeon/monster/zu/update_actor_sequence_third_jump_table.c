#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

extern void update_actor_sequence_third(ActorRecord *owner_input, ObjectPosition *motion_input, SpriteFrameState *actor_input, ActorRecord *object);

/* jump_table; owner: dungeon/func_80F95240. */
const void *const D_80164838[7] __attribute__((aligned(4))) = {
    ((u8 *)update_actor_sequence_third + 0x11C),
    ((u8 *)update_actor_sequence_third + 0x114),
    ((u8 *)update_actor_sequence_third + 0x10C),
    ((u8 *)update_actor_sequence_third + 0x124),
    ((u8 *)update_actor_sequence_third + 0xCC),
    ((u8 *)update_actor_sequence_third + 0xC4),
    ((u8 *)update_actor_sequence_third + 0xBC)
};
