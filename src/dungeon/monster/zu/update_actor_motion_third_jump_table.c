#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

extern void update_actor_motion_third(ActorRecord *actor, ObjectPosition *context, SpriteFrameState *sprite, ActorRecord *stats_in);

/* jump_table; owner: dungeon/func_80F93938. */
const void *const D_80164808[12] __attribute__((aligned(4))) = {
    ((u8 *)update_actor_motion_third + 0x434),
    ((u8 *)update_actor_motion_third + 0x434),
    ((u8 *)update_actor_motion_third + 0x434),
    ((u8 *)update_actor_motion_third + 0x460),
    ((u8 *)update_actor_motion_third + 0x3E0),
    ((u8 *)update_actor_motion_third + 0x3E0),
    ((u8 *)update_actor_motion_third + 0x3E0),
    ((u8 *)update_actor_motion_third + 0x3A8),
    ((u8 *)update_actor_motion_third + 0x38C),
    ((u8 *)update_actor_motion_third + 0x460),
    ((u8 *)update_actor_motion_third + 0x460),
    ((u8 *)update_actor_motion_third + 0x424)
};
