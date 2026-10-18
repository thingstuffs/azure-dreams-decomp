#include "common.h"

/* Four word callback ABI; primary dispatch and individual return-boundary evidence accompany this draft. */
extern s32 interpolate_actor_to_terrain_tile();
extern void dispatch_target_action();

void interpolate_actor_to_terrain_tile_and_dispatch(void *actor, void *motion, void *render, void *context)
{
    if (interpolate_actor_to_terrain_tile(actor, motion, render, context)) {
        *(void (**)(void *, void *, void *, void *))((u8 *)actor + 0x8C) = dispatch_target_action;
    }
}
