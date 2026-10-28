#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

extern void update_actor_action_and_facing(ActorRecord *actor, ObjectPosition *context, SpriteFrameState *sprite, ActorRecord *stats_in);

/* jump_table; owner: dungeon/func_80FAB938. */
const void *const zu_slot_a_behavior_targets[12] __attribute__((aligned(4))) = {
    ((u8 *)update_actor_action_and_facing + 0x434),
    ((u8 *)update_actor_action_and_facing + 0x434),
    ((u8 *)update_actor_action_and_facing + 0x434),
    ((u8 *)update_actor_action_and_facing + 0x460),
    ((u8 *)update_actor_action_and_facing + 0x3E0),
    ((u8 *)update_actor_action_and_facing + 0x3E0),
    ((u8 *)update_actor_action_and_facing + 0x3E0),
    ((u8 *)update_actor_action_and_facing + 0x3A8),
    ((u8 *)update_actor_action_and_facing + 0x38C),
    ((u8 *)update_actor_action_and_facing + 0x460),
    ((u8 *)update_actor_action_and_facing + 0x460),
    ((u8 *)update_actor_action_and_facing + 0x424)
};
