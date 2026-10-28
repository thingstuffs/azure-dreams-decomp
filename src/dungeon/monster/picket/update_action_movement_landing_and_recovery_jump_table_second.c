#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

extern void update_action_movement_landing_and_recovery(ActorRecord *action, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor);

/* jump_table; owner: dungeon/func_80E93490. */
const void *const D_8016A880[7] __attribute__((aligned(4))) = {
    ((u8 *)update_action_movement_landing_and_recovery + 0x15C),
    ((u8 *)update_action_movement_landing_and_recovery + 0x154),
    ((u8 *)update_action_movement_landing_and_recovery + 0x14C),
    ((u8 *)update_action_movement_landing_and_recovery + 0x164),
    ((u8 *)update_action_movement_landing_and_recovery + 0x108),
    ((u8 *)update_action_movement_landing_and_recovery + 0x100),
    ((u8 *)update_action_movement_landing_and_recovery + 0xF8)
};
