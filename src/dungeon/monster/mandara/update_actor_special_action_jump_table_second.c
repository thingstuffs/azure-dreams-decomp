#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

extern void update_actor_special_action(ActorRecord *self_object, ObjectPosition *aux_entity, SpriteFrameState *sprite, ActorRecord *entity);

/* jump_table; owner: dungeon/func_80FC976C. */
const void *const D_80158820[12] __attribute__((aligned(4))) = {
    ((u8 *)update_actor_special_action + 0x828),
    ((u8 *)update_actor_special_action + 0x828),
    ((u8 *)update_actor_special_action + 0x828),
    ((u8 *)update_actor_special_action + 0x854),
    ((u8 *)update_actor_special_action + 0x7D4),
    ((u8 *)update_actor_special_action + 0x7D4),
    ((u8 *)update_actor_special_action + 0x7D4),
    ((u8 *)update_actor_special_action + 0x76C),
    ((u8 *)update_actor_special_action + 0x76C),
    ((u8 *)update_actor_special_action + 0x854),
    ((u8 *)update_actor_special_action + 0x854),
    ((u8 *)update_actor_special_action + 0x818)
};
