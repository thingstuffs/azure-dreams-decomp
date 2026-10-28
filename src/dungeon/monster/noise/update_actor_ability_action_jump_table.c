#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

extern void update_actor_ability_action(void *action, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor);

/* jump_table; owner: dungeon/func_80D37E4C. */
const void *const D_8014C858[7] __attribute__((aligned(4))) = {
    ((u8 *)update_actor_ability_action + 0x120),
    ((u8 *)update_actor_ability_action + 0x118),
    ((u8 *)update_actor_ability_action + 0x110),
    ((u8 *)update_actor_ability_action + 0x128),
    ((u8 *)update_actor_ability_action + 0xD0),
    ((u8 *)update_actor_ability_action + 0xC8),
    ((u8 *)update_actor_ability_action + 0xC0)
};
