#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

extern void update_creature_action_and_animation(ActorRecord *self_object, ObjectPosition *aux_entity, SpriteFrameState *sprite, ActorRecord *entity);

/* jump_table; owner: dungeon/func_80FD576C. */
const void *const D_8014C820[12] __attribute__((aligned(4))) = {
    ((u8 *)update_creature_action_and_animation + 0x828),
    ((u8 *)update_creature_action_and_animation + 0x828),
    ((u8 *)update_creature_action_and_animation + 0x828),
    ((u8 *)update_creature_action_and_animation + 0x854),
    ((u8 *)update_creature_action_and_animation + 0x7D4),
    ((u8 *)update_creature_action_and_animation + 0x7D4),
    ((u8 *)update_creature_action_and_animation + 0x7D4),
    ((u8 *)update_creature_action_and_animation + 0x76C),
    ((u8 *)update_creature_action_and_animation + 0x76C),
    ((u8 *)update_creature_action_and_animation + 0x854),
    ((u8 *)update_creature_action_and_animation + 0x854),
    ((u8 *)update_creature_action_and_animation + 0x818)
};
