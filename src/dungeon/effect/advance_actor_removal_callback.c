#include "common.h"
#include "dungeon/actor.h"

/* Four word callback ABI; primary dispatch and individual return-boundary evidence accompany this draft. */


void advance_actor_removal_callback(void *actor, void *motion, void *render, void *context)
{
    advance_actor_removal(actor, motion, render, context);
}
