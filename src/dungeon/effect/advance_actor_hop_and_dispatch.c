#include "common.h"
#include "dungeon/effect.h"
#include "dungeon/actor.h"

/* Runs the actor hop-and-grow step and installs dispatch_target_action when it completes. */
void advance_actor_hop_and_dispatch(ActorRecord *actor, ObjectPosition *motion, SpriteFrameState *render, ActorRecord *context)
{
    if (update_actor_hop_and_grow(actor, motion, render, context)) {
        actor->unk_8C.address = dispatch_target_action;
    }
}
