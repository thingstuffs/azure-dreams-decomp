#include "common.h"
#include "dungeon/actor.h"

/* Four word callback ABI; primary dispatch and individual return-boundary evidence accompany this draft. */


void advance_actor_removal_callback(void *actor, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *context)
{
    advance_actor_removal(actor, motion, sprite, context);
}
