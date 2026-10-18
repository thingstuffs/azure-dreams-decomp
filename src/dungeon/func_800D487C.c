#include "common.h"

/* Four word callback ABI; primary dispatch and individual return-boundary evidence accompany this draft. */
extern s32 update_actor_hop_and_grow();
extern void update_actor_facing_animation();

void update_actor_hop_and_grow_callback(void *actor, void *motion, void *render, void *context)
{
    if (update_actor_hop_and_grow(actor, motion, render, context)) {
        *(void (**)(void *, void *, void *, void *))((u8 *)actor + 0x8C) = update_actor_facing_animation;
    }
}
