#include "common.h"
#include "dungeon/effect.h"

/* Four word callback ABI; primary dispatch and individual return-boundary evidence accompany this draft. */
extern s32 update_actor_fade_in();

/* Runs the actor fade-in step and installs dispatch_target_action when it completes. */
void advance_actor_fade_in_and_dispatch(void *actor, void *motion, void *render, void *context)
{
    if (update_actor_fade_in(actor, motion, render, context)) {
        *(void (**)(void *, void *, void *, void *))((u8 *)actor + 0x8C) = dispatch_target_action;
    }
}
