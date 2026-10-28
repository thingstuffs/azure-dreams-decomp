#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

extern void advance_ability_action_and_reset_state(void *action, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor);

/* jump_table; owner: dungeon/func_80D25E4C. */
const void *const D_8015E858[7] __attribute__((aligned(4))) = {
    ((u8 *)advance_ability_action_and_reset_state + 0x120),
    ((u8 *)advance_ability_action_and_reset_state + 0x118),
    ((u8 *)advance_ability_action_and_reset_state + 0x110),
    ((u8 *)advance_ability_action_and_reset_state + 0x128),
    ((u8 *)advance_ability_action_and_reset_state + 0xD0),
    ((u8 *)advance_ability_action_and_reset_state + 0xC8),
    ((u8 *)advance_ability_action_and_reset_state + 0xC0)
};
