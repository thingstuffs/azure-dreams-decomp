#include "common.h"
#include "dungeon/actor.h"

/* Forward all four effect callback arguments and the result. */
s32 forward_actor_defeat_removal_second(ActorRecord *state, s32 *position, SpriteFrameState *sprite, ActorRecord *entity_data) {
    return update_actor_defeat_removal(state, position, sprite, entity_data);
}
