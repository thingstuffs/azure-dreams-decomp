#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "common.h"

void update_actor_targeted_action(ActorRecord *action, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor);

/* jump_table; owner: dungeon/func_80EE1FB0. */
const void *const D_80170888[5] __attribute__((aligned(4))) = {
    ((u8 *)update_actor_targeted_action + 0x60),
    ((u8 *)update_actor_targeted_action + 0x298),
    ((u8 *)update_actor_targeted_action + 0x2E0),
    ((u8 *)update_actor_targeted_action + 0x434),
    ((u8 *)update_actor_targeted_action + 0x448)
};
