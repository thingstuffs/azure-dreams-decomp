#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

extern void update_actor_item_action(ActorRecord *action, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor);

/* jump_table; owner: dungeon/func_80F05FB0. */
const void *const D_8014C8A0[7] __attribute__((aligned(4))) = {
    ((u8 *)update_actor_item_action + 0x110),
    ((u8 *)update_actor_item_action + 0x108),
    ((u8 *)update_actor_item_action + 0x100),
    ((u8 *)update_actor_item_action + 0x118),
    ((u8 *)update_actor_item_action + 0xBC),
    ((u8 *)update_actor_item_action + 0xB4),
    ((u8 *)update_actor_item_action + 0xAC)
};
