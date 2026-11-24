#include "dungeon/actor/effect.h"
#include "dungeon/monster/kid.h"

void resume_kid_behavior_after_fade_in(ActorRecord *actor, ObjectPosition *motion, SpriteFrameState *sprite)
{
    if (update_actor_fade_in(actor, motion, sprite)) {
        actor->unk_8C.address = update_kid_behavior;
    }
}
