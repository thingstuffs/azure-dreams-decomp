#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

extern void advance_actor_item_action_and_recovery(ActorRecord *action_state, ObjectPosition *transform, SpriteFrameState *sprite, ActorRecord *actor);

/* jump_table; owner: dungeon/func_80FD75EC. */
const void *const D_8014C850[7] __attribute__((aligned(4))) = {
    ((u8 *)advance_actor_item_action_and_recovery + 0x11C),
    ((u8 *)advance_actor_item_action_and_recovery + 0x114),
    ((u8 *)advance_actor_item_action_and_recovery + 0x10C),
    ((u8 *)advance_actor_item_action_and_recovery + 0x124),
    ((u8 *)advance_actor_item_action_and_recovery + 0xCC),
    ((u8 *)advance_actor_item_action_and_recovery + 0xC4),
    ((u8 *)advance_actor_item_action_and_recovery + 0xBC)
};
