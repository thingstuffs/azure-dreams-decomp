#include "common.h"
#include "dungeon/effect.h"
#include "dungeon/actor.h"
struct ActorHopExtra;
struct ActorHopMotion;
struct ActorHopParams;
struct ActorHopState;

/* Four word callback ABI; primary dispatch and individual return-boundary evidence accompany this draft. */

/* Runs the actor hop-and-grow step and installs dispatch_target_action when it completes. */
void advance_actor_hop_and_dispatch(void *actor, void *motion, void *render, void *context)
{
    if (update_actor_hop_and_grow(actor, motion, render, context)) {
        *(void (**)(void *, void *, void *, void *))((u8 *)actor + 0x8C) = dispatch_target_action;
    }
}
