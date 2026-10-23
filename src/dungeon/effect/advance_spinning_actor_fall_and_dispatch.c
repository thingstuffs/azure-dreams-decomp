#include "common.h"
#include "dungeon/effect.h"

/* Four word callback ABI; primary dispatch and individual return-boundary evidence accompany this draft. */
extern s32 update_spinning_actor_fall();

/* Runs the spinning actor fall step and installs dispatch_target_action when it completes. */
void advance_spinning_actor_fall_and_dispatch(void *actor, void *motion, void *render, void *context)
{
    if (update_spinning_actor_fall(actor, motion, render, context)) {
        *(void (**)(void *, void *, void *, void *))((u8 *)actor + 0x8C) = dispatch_target_action;
    }
}
