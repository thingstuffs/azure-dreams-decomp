#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

extern void update_complex_actor_action_state(ActorRecord *self_object, ObjectPosition *aux_entity, SpriteFrameState *sprite, ActorRecord *entity);

/* jump_table; owner: dungeon/func_80FB776C. */
const void *const D_8016A820[12] __attribute__((aligned(4))) = {
    ((u8 *)update_complex_actor_action_state + 0x828),
    ((u8 *)update_complex_actor_action_state + 0x828),
    ((u8 *)update_complex_actor_action_state + 0x828),
    ((u8 *)update_complex_actor_action_state + 0x854),
    ((u8 *)update_complex_actor_action_state + 0x7D4),
    ((u8 *)update_complex_actor_action_state + 0x7D4),
    ((u8 *)update_complex_actor_action_state + 0x7D4),
    ((u8 *)update_complex_actor_action_state + 0x76C),
    ((u8 *)update_complex_actor_action_state + 0x76C),
    ((u8 *)update_complex_actor_action_state + 0x854),
    ((u8 *)update_complex_actor_action_state + 0x854),
    ((u8 *)update_complex_actor_action_state + 0x818)
};
