#include "dungeon/actor.h"
#include "dungeon/monster/blume.h"

void resume_blume_actions_after_hop(ActorRecord *actor, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *context)
{
    if (update_actor_hop_and_grow(actor, motion, sprite, context)) {
        actor->unk_8C.address = dispatch_blume_actions;
    }
}
