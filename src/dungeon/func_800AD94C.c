#include "common.h"

/* Four word callback ABI; primary dispatch and individual return-boundary evidence accompany this draft. */
extern s32 update_actor_hop_and_grow();
extern void dispatch_target_action();

void advance_actor_hop_and_dispatch(void *actor, void *motion, void *render, void *context)
{
    if (update_actor_hop_and_grow(actor, motion, render, context)) {
        *(void (**)(void *, void *, void *, void *))((u8 *)actor + 0x8C) = dispatch_target_action;
    }
}
