#include "shared/sprite_frame_state.h"
#include "shared/entity.h"
#include "common.h"

extern s32 update_actor_defeat_removal(ActorRecord *state, ObjectPosition *position, SpriteFrameState *sprite, ActorRecord *entity_data);

/* Forward all four effect callback arguments and the result. */
s32 update_nyuel_defeat_removal_slot_d(ActorRecord *state, ObjectPosition *position, SpriteFrameState *sprite, ActorRecord *entity_data) {
    return update_actor_defeat_removal(state, position, sprite, entity_data);
}
