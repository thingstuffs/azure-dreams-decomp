#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

extern void update_actor_ability_action_2(ActorRecord *action, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor);

/* jump_table; owner: dungeon/func_80EF9FB0. */
const void *const D_80158888[5] __attribute__((aligned(4))) = {
    ((u8 *)update_actor_ability_action_2 + 0x60),
    ((u8 *)update_actor_ability_action_2 + 0x298),
    ((u8 *)update_actor_ability_action_2 + 0x2E0),
    ((u8 *)update_actor_ability_action_2 + 0x434),
    ((u8 *)update_actor_ability_action_2 + 0x448)
};
