#include "dungeon/actor/effect.h"
#include "dungeon/monster/blume.h"

void resume_blume_actions_after_fade_in(ActorRecord *actor, ObjectPosition *motion, SpriteFrameState *sprite)
{
    if (update_actor_fade_in(actor, motion, sprite)) {
        actor->unk_8C.address = dispatch_blume_actions;
    }
}
