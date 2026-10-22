#include "common.h"
#include "dungeon/actor.h"

/* Four word callback ABI; primary dispatch and individual return-boundary evidence accompany this draft. */
extern s32 update_linked_actor_motion(void *, void *, void *, void *);
extern s32 check_actor_floor_trap();

void update_linked_actor_motion_and_check_floor_trap(void *actor, void *motion, void *render, void *context)
{
    if (update_linked_actor_motion(actor, motion, render, context) &&
        ((s16)check_actor_floor_trap(render, context) > 0)) {
        *(void (**)(void *, void *, void *, void *))((u8 *)actor + 0x8C) = update_actor_facing_animation;
    }
}
