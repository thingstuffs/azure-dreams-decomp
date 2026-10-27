#include "shared/sprite_frame_state.h"
#include "shared/entity.h"
#include "common.h"

void update_long_actor_action(ActorRecord *self_object, ObjectPosition *aux_entity, SpriteFrameState *sprite, ActorRecord *entity);

/* Exact jump_table span; dispatch consumer dungeon/func_80FB176C. */
const void *const mandara_slot_g_behavior_targets[5] __attribute__((aligned(4))) = {
    ((u8 *)update_long_actor_action + 0x1C0),
    ((u8 *)update_long_actor_action + 0x22C),
    ((u8 *)update_long_actor_action + 0x300),
    ((u8 *)update_long_actor_action + 0x490),
    ((u8 *)update_long_actor_action + 0x4D8)
};
