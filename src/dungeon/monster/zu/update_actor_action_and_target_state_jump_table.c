#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

extern void update_actor_action_and_target_state(ActorRecord *actor, ObjectPosition *context, SpriteFrameState *sprite, ActorRecord *stats_in);

/* jump_table; owner: dungeon/func_80FA5938. */
const void *const D_80152808[12] __attribute__((aligned(4))) = {
    ((u8 *)update_actor_action_and_target_state + 0x434),
    ((u8 *)update_actor_action_and_target_state + 0x434),
    ((u8 *)update_actor_action_and_target_state + 0x434),
    ((u8 *)update_actor_action_and_target_state + 0x460),
    ((u8 *)update_actor_action_and_target_state + 0x3E0),
    ((u8 *)update_actor_action_and_target_state + 0x3E0),
    ((u8 *)update_actor_action_and_target_state + 0x3E0),
    ((u8 *)update_actor_action_and_target_state + 0x3A8),
    ((u8 *)update_actor_action_and_target_state + 0x38C),
    ((u8 *)update_actor_action_and_target_state + 0x460),
    ((u8 *)update_actor_action_and_target_state + 0x460),
    ((u8 *)update_actor_action_and_target_state + 0x424)
};
