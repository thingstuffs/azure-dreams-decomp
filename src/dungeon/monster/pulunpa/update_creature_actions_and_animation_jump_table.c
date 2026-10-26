#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "common.h"

void update_creature_actions_and_animation(ActorRecord *actor, ObjectPosition *context, SpriteFrameState *sprite, ActorRecord *creature);

/* jump_table; owner: dungeon/func_80CC0398. */
const void *const D_80170858[12] __attribute__((aligned(4))) = {
    ((u8 *)update_creature_actions_and_animation + 0x360),
    ((u8 *)update_creature_actions_and_animation + 0x360),
    ((u8 *)update_creature_actions_and_animation + 0x360),
    ((u8 *)update_creature_actions_and_animation + 0x370),
    ((u8 *)update_creature_actions_and_animation + 0x360),
    ((u8 *)update_creature_actions_and_animation + 0x360),
    ((u8 *)update_creature_actions_and_animation + 0x360),
    ((u8 *)update_creature_actions_and_animation + 0x360),
    ((u8 *)update_creature_actions_and_animation + 0x33C),
    ((u8 *)update_creature_actions_and_animation + 0x370),
    ((u8 *)update_creature_actions_and_animation + 0x370),
    ((u8 *)update_creature_actions_and_animation + 0x360)
};
