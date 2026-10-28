#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

extern void update_actor_action_sequence_and_recovery(ActorRecord *self_object, ObjectPosition *aux_entity, SpriteFrameState *sprite, ActorRecord *entity);

/* jump_table; owner: dungeon/func_80FC376C. */
const void *const mandara_slot_d_behavior_targets[5] __attribute__((aligned(4))) = {
    ((u8 *)update_actor_action_sequence_and_recovery + 0x1C0),
    ((u8 *)update_actor_action_sequence_and_recovery + 0x22C),
    ((u8 *)update_actor_action_sequence_and_recovery + 0x300),
    ((u8 *)update_actor_action_sequence_and_recovery + 0x490),
    ((u8 *)update_actor_action_sequence_and_recovery + 0x4D8)
};
