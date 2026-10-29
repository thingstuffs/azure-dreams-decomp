#include "shared/sprite_frame_state.h"
#include "shared/entity.h"
#include "common.h"
#include "dungeon/monster/kewne.h"
#include "dungeon/actor.h"

/* Forward all four effect callback arguments and the result. */
s32 update_kewne_defeat_removal_slot_c(ActorRecord *state, ObjectPosition *position, SpriteFrameState *sprite, ActorRecord *entity_data) {
    return update_actor_defeat_removal(state, position, sprite, entity_data);
}
