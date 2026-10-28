#include "common.h"
#include "shared/entity.h"

extern void advance_actor_ability_action_and_effects(void *action, ObjectPosition *motion, void *sprite, ActorRecord *actor);

/* jump_table; owner: dungeon/func_80A430C4. */
const void *const D_8014C858[7] __attribute__((aligned(4))) = {
    ((u8 *)advance_actor_ability_action_and_effects + 0x128),
    ((u8 *)advance_actor_ability_action_and_effects + 0x120),
    ((u8 *)advance_actor_ability_action_and_effects + 0x118),
    ((u8 *)advance_actor_ability_action_and_effects + 0x130),
    ((u8 *)advance_actor_ability_action_and_effects + 0xD8),
    ((u8 *)advance_actor_ability_action_and_effects + 0xD0),
    ((u8 *)advance_actor_ability_action_and_effects + 0xC8)
};
