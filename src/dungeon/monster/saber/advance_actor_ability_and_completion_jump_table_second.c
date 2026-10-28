#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

extern void advance_actor_ability_and_completion(void *action_in, ObjectPosition *motion_in, SpriteFrameState *sprite, void *actor);

/* jump_table; owner: dungeon/func_80ADFA30. */
const void *const saber_slot_c_extra_action_targets[7] __attribute__((aligned(4))) = {
    ((u8 *)advance_actor_ability_and_completion + 0x11C),
    ((u8 *)advance_actor_ability_and_completion + 0x114),
    ((u8 *)advance_actor_ability_and_completion + 0x10C),
    ((u8 *)advance_actor_ability_and_completion + 0x124),
    ((u8 *)advance_actor_ability_and_completion + 0xC8),
    ((u8 *)advance_actor_ability_and_completion + 0xC0),
    ((u8 *)advance_actor_ability_and_completion + 0xB8)
};
