#include "dungeon/actor/effect.h"
#include "dungeon/monster/blume.h"

void resume_blume_actions_after_spinning_fall(ActorRecord *actor, ObjectPosition *motion, SpriteFrameState *sprite, void *context)
{
    if (update_spinning_actor_fall(actor, motion, sprite, context)) {
        actor->unk_8C.address = dispatch_blume_actions;
    }
}
