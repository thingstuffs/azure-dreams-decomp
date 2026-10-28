#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

extern void update_actor_action_fourth(ActorRecord *controller, ObjectPosition *context, SpriteFrameState *entity, ActorRecord *actor_state);

/* jump_table; owner: dungeon/func_80A35684. */
const void *const ifrit_slot_c_behavior_targets[12] __attribute__((aligned(4))) = {
    ((u8 *)update_actor_action_fourth + 0x3C8),
    ((u8 *)update_actor_action_fourth + 0x3C8),
    ((u8 *)update_actor_action_fourth + 0x3C8),
    ((u8 *)update_actor_action_fourth + 0x3F4),
    ((u8 *)update_actor_action_fourth + 0x374),
    ((u8 *)update_actor_action_fourth + 0x374),
    ((u8 *)update_actor_action_fourth + 0x374),
    ((u8 *)update_actor_action_fourth + 0x33C),
    ((u8 *)update_actor_action_fourth + 0x33C),
    ((u8 *)update_actor_action_fourth + 0x3F4),
    ((u8 *)update_actor_action_fourth + 0x3F4),
    ((u8 *)update_actor_action_fourth + 0x3B8)
};
