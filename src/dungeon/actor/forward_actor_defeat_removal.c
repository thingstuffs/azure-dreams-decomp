#include "common.h"
#include "dungeon/actor.h"

/* Forward all four effect callback arguments and the result. */
s32 forward_actor_defeat_removal(ActorRecord *body, s32 *position, SpriteFrameState *sprite, ActorRecord *actor) {
    return update_actor_defeat_removal(body, position, sprite, actor);
}
