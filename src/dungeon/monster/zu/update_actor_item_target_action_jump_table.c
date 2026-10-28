#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

extern void update_actor_item_target_action(ActorRecord *owner_input, ObjectPosition *motion_input, SpriteFrameState *actor_input, ActorRecord *object);

/* jump_table; owner: dungeon/func_80FAD240. */
const void *const zu_slot_a_action_targets[7] __attribute__((aligned(4))) = {
    ((u8 *)update_actor_item_target_action + 0x11C),
    ((u8 *)update_actor_item_target_action + 0x114),
    ((u8 *)update_actor_item_target_action + 0x10C),
    ((u8 *)update_actor_item_target_action + 0x124),
    ((u8 *)update_actor_item_target_action + 0xCC),
    ((u8 *)update_actor_item_target_action + 0xC4),
    ((u8 *)update_actor_item_target_action + 0xBC)
};
