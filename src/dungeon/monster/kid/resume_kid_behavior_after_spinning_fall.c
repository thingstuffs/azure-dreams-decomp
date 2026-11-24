#include "dungeon/actor/effect.h"
#include "dungeon/monster/kid.h"

void resume_kid_behavior_after_spinning_fall(ActorRecord *actor, ObjectPosition *motion, SpriteFrameState *sprite, void *context)
{
    if (update_spinning_actor_fall(actor, motion, sprite, context)) {
        actor->unk_8C.address = update_kid_behavior;
    }
}
